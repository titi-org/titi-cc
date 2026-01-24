%code top {
    #define _GNU_SOURCE
}

%code requires {
    #include "val.h"
}

%code {
    #include <ctype.h>
    #include "cc.h"


    
    int real_error(yyscan_t scanner, val_callback_t callback, const char *msg) {
        (void)callback;
        PARSER_ERROR(scanner, "%s at '%s'", msg, top_get_text(scanner));
        return 0;
    }

    #define real_lex bridging_lex

    static TypeKind merge_type_kind(TypeKind left, TypeKind right) {
        if (left == TYPE_KIND_NONE)
            return right;
        if (right == TYPE_KIND_NONE)
            return left;
        if (left == TYPE_KIND_OTHER || right == TYPE_KIND_OTHER)
            return TYPE_KIND_OTHER;
        if (left == right)
            return left;
        return TYPE_KIND_OTHER;
    }

    static TypeSpecInfo make_type_spec(const char *full, const char *stripped,
                                       TypeKind kind, unsigned int type_count,
                                       unsigned int qualifier_count,
                                       unsigned int has_struct_union) {
        TypeSpecInfo spec;
        spec.full = strdup(full ? full : "");
        spec.stripped = strdup(stripped ? stripped : "");
        spec.kind = kind;
        spec.type_count = type_count;
        spec.qualifier_count = qualifier_count;
        spec.has_struct_union = has_struct_union;
        return spec;
    }

    static TypeSpecInfo merge_type_specs(TypeSpecInfo left, TypeSpecInfo right) {
        TypeSpecInfo merged;
        safe_asprintf(&merged.full, "%s %s", left.full, right.full);

        if (left.stripped && left.stripped[0]) {
            if (right.stripped && right.stripped[0]) {
                safe_asprintf(&merged.stripped, "%s %s", left.stripped, right.stripped);
            } else {
                merged.stripped = strdup(left.stripped);
            }
        } else if (right.stripped && right.stripped[0]) {
            merged.stripped = strdup(right.stripped);
        } else {
            merged.stripped = strdup("");
        }

        merged.kind = merge_type_kind(left.kind, right.kind);
        merged.type_count = left.type_count + right.type_count;
        merged.qualifier_count = left.qualifier_count + right.qualifier_count;
        merged.has_struct_union =
            left.has_struct_union || right.has_struct_union;

        free(left.full);
        free(left.stripped);
        free(right.full);
        free(right.stripped);
        return merged;
    }

    static SimpleCastKind simple_cast_kind(TypeSpecInfo spec,
                                           int has_abstract_decl) {
        if (has_abstract_decl)
            return SIMPLE_CAST_NONE;
        if (spec.type_count != 1 || spec.qualifier_count != 0)
            return SIMPLE_CAST_NONE;
        switch (spec.kind) {
            case TYPE_KIND_INT:
                return SIMPLE_CAST_INT;
            case TYPE_KIND_LONG:
                return SIMPLE_CAST_LONG;
            case TYPE_KIND_RUN_OBJ_T:
                return SIMPLE_CAST_RUN_OBJ_T;
            default:
                return SIMPLE_CAST_NONE;
        }
    }

    static char *dup_range(const char *start, size_t len) {
        char *s = malloc(len + 1);
        if (!s)
            return NULL;
        memcpy(s, start, len);
        s[len] = '\0';
        return s;
    }

    static size_t find_top_level_comma(const char *text) {
        size_t i = 0;
        int depth = 0;
        int in_string = 0;
        while (text && text[i]) {
            char c = text[i];
            if (in_string) {
                if (c == '\\' && text[i + 1]) {
                    i += 2;
                    continue;
                }
                if (c == '"')
                    in_string = 0;
                i++;
                continue;
            }
            if (c == '"') {
                in_string = 1;
                i++;
                continue;
            }
            if (c == '(' || c == '[' || c == '{') {
                depth++;
            } else if (c == ')' || c == ']' || c == '}') {
                if (depth > 0)
                    depth--;
            } else if (c == ',' && depth == 0) {
                return i;
            }
            i++;
        }
        return (size_t)-1;
    }

    static char *replace_percent_ld(const char *text) {
        if (!text)
            return NULL;
        size_t len = strlen(text);
        char *out = malloc(len + 1);
        if (!out)
            return NULL;
        size_t i = 0;
        size_t j = 0;
        int in_string = 0;
        int changed = 0;
        while (i < len) {
            char c = text[i];
            if (in_string) {
                if (c == '\\' && i + 1 < len) {
                    out[j++] = text[i++];
                    out[j++] = text[i++];
                    continue;
                }
                if (c == '"') {
                    in_string = 0;
                    out[j++] = c;
                    i++;
                    continue;
                }
                if (c == '%' && i + 2 < len && text[i + 1] == 'l' &&
                    text[i + 2] == 'd' && !(i > 0 && text[i - 1] == '%')) {
                    out[j++] = '%';
                    out[j++] = 'd';
                    i += 3;
                    changed = 1;
                    continue;
                }
            } else if (c == '"') {
                in_string = 1;
            }
            out[j++] = c;
            i++;
        }
        out[j] = '\0';
        if (!changed) {
            free(out);
            return NULL;
        }
        return out;
    }

    static char *adjust_printf_args(const char *args_text) {
        if (!args_text)
            return NULL;

        size_t comma_pos = find_top_level_comma(args_text);
        if (comma_pos == (size_t)-1)
            return NULL;

        char *first = dup_range(args_text, comma_pos);
        if (!first)
            return NULL;

        const char *second = args_text + comma_pos + 1;
        while (*second && isspace((unsigned char)*second))
            second++;
        if (!isalpha((unsigned char)*second) && *second != '_') {
            free(first);
            return NULL;
        }

        const char *name_start = second;
        second++;
        while (isalnum((unsigned char)*second) || *second == '_')
            second++;
        char *name = dup_range(name_start, (size_t)(second - name_start));
        if (!name) {
            free(first);
            return NULL;
        }

        while (*second && isspace((unsigned char)*second))
            second++;
        if (*second != '(') {
            free(first);
            free(name);
            return NULL;
        }

        TypeKind ret_kind = lookup_function_return_kind(name);
        if (ret_kind != TYPE_KIND_INT) {
            free(first);
            free(name);
            return NULL;
        }

        char *new_first = replace_percent_ld(first);
        free(first);
        free(name);
        if (!new_first)
            return NULL;

        char *new_args = NULL;
        safe_asprintf(&new_args, "%s%s", new_first, args_text + comma_pos);
        free(new_first);
        return new_args;
    }
}

%define api.pure full
%define api.prefix {real_}
%debug
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { val_callback_t callback }

%define api.value.type {REAL_STYPE}

%token <str> IDENTIFIER 258
%token <str> CONSTANT 259
%token <str> STRING_LITERAL 260
%token <str> SIZEOF 261
%token <str> TYPE_NAME 262
%token <str> OFFSETOF 263
%token <str> RECURSIVE_ID 264
%token <str> PRINTF
/* RUN_FUNC removed - RUN token serves both morphism and run() definition */
%token <str> RUN 283
%token <str> EVAL 284
%token <str> COMPUTE 285
%token <str> PROGRAM 286
%token <str> DATA 287
%token <str> IDEMPOTENT 288
%token <str> SWAP 290
%token <str> COPY 291
%token <str> DELETE 292
%token <str> FUNCTION 293
%token <str> PROCESS 294
%token <str> SEQUENTIAL 295
%token <str> PARALLEL 296
%token <str> PARTIAL 297
%token <str> FIXPOINT 298
%token <str> KLEENE 299
%token <str> IDENTITY 361
%token <str> ISEQ 362
%token <str> RHO 363
%token <str> BOOL_VALUE 364
%token CAT_PLUS 365
%token CAT_STAR 366
%token CAT_EQ 367
%token CAT_NE 368
%token CAT_BANG 369
%token PTR_OP 300
%token INC_OP 301
%token DEC_OP 302
%token LEFT_OP 303
%token RIGHT_OP 304
%token LE_OP 305
%token GE_OP 306
%token EQ_OP 307
%token NE_OP 308
%token AND_OP 309
%token OR_OP 310
%token MUL_ASSIGN 311
%token DIV_ASSIGN 312
%token MOD_ASSIGN 313
%token ADD_ASSIGN 314
%token SUB_ASSIGN 315
%token LEFT_ASSIGN 316
%token RIGHT_ASSIGN 317
%token AND_ASSIGN 318
%token XOR_ASSIGN 319
%token OR_ASSIGN 320
%token TYPEDEF 321
%token EXTERN 322
%token STATIC 323
%token AUTO 324
%token REGISTER 325
%token TYPEOF 326
%token INLINE 327
%token RESTRICT 328
%token CONST 329
%token VOLATILE 330
%token <str> STD_TYPE 331
%token STRUCT 332
%token UNION 333
%token ENUM 334
%token ELLIPSIS 335
%token CASE 336
%token DEFAULT 337
%token IF 338
%token ELSE 339
%token SWITCH 341
%token WHILE 342
%token DO 343
%token FOR 344
%token GOTO 345
%token CONTINUE 346
%token BREAK 347
%token RETURN 348
%token MODE_MARKER_C_TO_RUN 349
%token MODE_MARKER_PASSTHROUGH 350
%token MODE_MARKER_DISCOVERY 351
%token <str> LBRACE 352 "{"
%token <str> RBRACE 353 "}"

%token START_TOP 1001
%token START_DECL 1002
%token START_STMT 1003
%token START_EXPR 1004
%token START_NAT 1005
%token START_BOOL 1006

%token <str> RUN_CC_ADD RUN_CC_SUB RUN_CC_MUL RUN_CC_DIV RUN_CC_MOD
%token <str> RUN_CC_GT RUN_CC_LT RUN_CC_GE RUN_CC_LE RUN_CC_EQ RUN_CC_NE
%token <str> RUN_CC_AND RUN_CC_OR RUN_CC_NOT RUN_CC_IFTE
%token <str> IFTE 340
%token <str> CONSTEXPR 354
%token <str> STATIC_ASSERT 355
%token <str> THREAD_LOCAL 356
%token <str> ALIGNAS 357
%token <str> ALIGNOF 358
%token LEFT_BRACKET_BRACKET 1024
%token RIGHT_BRACKET_BRACKET 1025
%token <str> RUN_CC_CONSTANT 1023
%token <str> TYPE_INT
%token <str> TYPE_VOID
%token <str> TYPE_LONG
%token <str> TYPE_RUN_OBJ_T

%start entry

%type <type_name> type_name
%type <str> function_header
%type <decl> function_declarator
%type <str> declaration struct_or_union_specifier struct_or_union struct_declaration_list struct_declaration struct_declarator_list_full struct_declarator_full enum_specifier enumerator_list enumerator init_declarator_list_full init_declarator_full declarator_full direct_declarator_full pointer type_qualifier_list parameter_type_list parameter_list parameter_declaration identifier_list initializer initializer_list abstract_declarator direct_abstract_declarator static_assert_declaration block_item block_item_list bracket_static_expression designation designator_list designator
%type <type_spec> declaration_specifiers declaration_specifier storage_class_specifier type_specifier_atomic type_qualifier specifier_qualifier_list specifier_qualifier
%type <val> expression constant_expression assignment_expression conditional_expression logical_or_expression logical_and_expression inclusive_or_expression exclusive_or_expression and_expression equality_expression relational_expression shift_expression additive_expression multiplicative_expression cast_expression unary_expression postfix_expression primary_expression argument_expression_list recursive_call if_prefix while_prefix
%type <str> assignment_operator pavlovic_operator string_literal_sequence generic_identifier any_id attribute_specifier_list attribute_specifier_list_opt attribute_specifier attribute_list attribute attribute_token attribute_scoped_token attribute_argument_clause_opt label statement compound_statement expression_statement selection_statement iteration_statement jump_statement statement_list labeled_statement static_assert_tail

%%

entry:
  START_TOP translation_unit { YYACCEPT; }
| START_DECL declaration { if (callback) callback((val_ptr)$2); YYACCEPT; }
| START_STMT statement_list { YYACCEPT; }
| START_EXPR expression { if (callback) callback($2); YYACCEPT; }
;

/* TOP Level */
translation_unit: translation_unit_inner ;

translation_unit_inner
	: external_declaration
	| dispatcher_marker external_declaration
	| translation_unit_inner external_declaration
	| translation_unit_inner dispatcher_marker external_declaration
	;

dispatcher_marker
	: MODE_MARKER_C_TO_RUN
	| MODE_MARKER_PASSTHROUGH
	| MODE_MARKER_DISCOVERY
	;

external_declaration
	: run_definition
	| function_definition
	| declaration { print_str($1); print_str("\n"); free($1); reset_params(); }
	| ';' { print_str(";\n"); reset_params(); }
	| error ';' { PARSER_RECOVER(scanner, "Recovered at ';'"); yyerrok; }
	| error '}' { PARSER_RECOVER(scanner, "Recovered at '}'"); yyerrok; }
	;

function_definition
    : function_header function_body { on_function_end(); pop_context(); reset_params(); }
    ;

function_header
    : attribute_specifier_list_opt declaration_specifiers function_declarator {
            on_function_header($1, $2, $3.text, $3.ptr_prefix);
            if ($1) free($1);
            if ($2.full) free($2.full);
            if ($2.stripped) free($2.stripped);
            free($3.text);
            free($3.ptr_prefix);
      }
    ;


declaration
    : attribute_specifier_list_opt declaration_specifiers init_declarator_list_full ';' { $$ = on_declaration($1, $2, $3); if (callback) callback((val_ptr)$$); on_declaration_end(); if ($1) free($1); free($2.full); free($2.stripped); free($3); }
	| attribute_specifier_list_opt declaration_specifiers ';' { $$ = on_declaration($1, $2, NULL); if (callback) callback((val_ptr)$$); on_declaration_end(); if ($1) free($1); free($2.full); free($2.stripped); }
	| static_assert_declaration { $$ = $1; if (callback) callback((val_ptr)$$); on_declaration_end(); }
    ;

static_assert_declaration
	: static_assert_prefix constant_expression static_assert_tail ')' ';' { pop_state(scanner); safe_asprintf(&$$, "static_assert ( %s %s ) ;", $2->text, $3); free_expr_info($2); free($3); }
	;

static_assert_prefix
	: STATIC_ASSERT { push_native_state(scanner); } '('
	;

static_assert_tail
	: ',' STRING_LITERAL { safe_asprintf(&$$, ", %s", $2); free($2); }
	| %empty { $$ = strdup(""); }
	;

run_definition
       : RUN '(' ')' {
               on_run_header();
               free($1);
       } function_body {
               on_function_end();
               pop_context();
               reset_params();
       }
       ;

function_body
	: LBRACE {
		RunCCContext *ctx = get_current_context();
		if (run_mode && should_emit_run() && ctx && !ctx->uses_aggregate &&
		    !needs_run_nat && !needs_run_bool) {
			push_native_state(scanner);
		}
	} block_item_list RBRACE {
		RunCCContext *ctx = get_current_context();
		char *body = stop_buffering();
		if (run_mode && should_emit_run() && ctx && !ctx->uses_aggregate &&
		    !needs_run_nat && !needs_run_bool) {
			pop_state(scanner);
		}
		if (should_emit_run() && ctx && !ctx->uses_aggregate) {
			emit_nested_step_full(ctx, body);
			print_str("}\n");
		} else {
			/* Passthrough: output body directly */
			print_str(" { "); if (body) print_str(body); print_str(" }\n");
		}
		if (body) free(body);
	  }
    | LBRACE {
		RunCCContext *ctx = get_current_context();
		if (run_mode && should_emit_run() && ctx && !ctx->uses_aggregate &&
		    !needs_run_nat && !needs_run_bool) {
			push_native_state(scanner);
		}
	} RBRACE {
		RunCCContext *ctx = get_current_context();
		if (run_mode && should_emit_run() && ctx && !ctx->uses_aggregate &&
		    !needs_run_nat && !needs_run_bool) {
			pop_state(scanner);
		}
		if (should_emit_run() && ctx && !ctx->uses_aggregate) {
			emit_nested_step_full(ctx, "");
			print_str("}\n");
		} else {
			/* Passthrough: empty body */
			print_str(" { }\n");
		}
    }
	;

/* Block Items */
block_item_list
    : block_item
    | block_item_list block_item
    ;

block_item
    : statement
    | declaration_specifiers init_declarator_list_full ';' { print_str($1.full); print_str(" "); print_str($2); print_str(" ; "); free($1.full); free($1.stripped); free($2); }
    | attribute_specifier_list declaration_specifiers init_declarator_list_full ';' { print_str($1); print_str(" "); print_str($2.full); print_str(" "); print_str($3); print_str(" ; "); free($1); free($2.full); free($2.stripped); free($3); }
    | error ';' { PARSER_RECOVER(scanner, "Recovered at ';'"); yyerrok; }
    ;

/* Declarations */
declaration_specifiers
	: declaration_specifier { $$ = $1; }
	| declaration_specifiers declaration_specifier { $$ = merge_type_specs($1, $2); }
	;

declaration_specifier
	: storage_class_specifier { $$ = $1; }
	| type_specifier_atomic { $$ = $1; }
	| type_qualifier { $$ = $1; }
	;

storage_class_specifier
	: TYPEDEF { on_storage_class_typedef(); $$ = make_type_spec("typedef", "", TYPE_KIND_NONE, 0, 0, 0); }
	| EXTERN { $$ = make_type_spec("extern", "", TYPE_KIND_NONE, 0, 0, 0); }
	| STATIC { $$ = make_type_spec("static", "", TYPE_KIND_NONE, 0, 0, 0); }
	| THREAD_LOCAL { $$ = make_type_spec("thread_local", "", TYPE_KIND_NONE, 0, 0, 0); }
	| AUTO { $$ = make_type_spec("auto", "", TYPE_KIND_NONE, 0, 0, 0); }
	| REGISTER { $$ = make_type_spec("register", "", TYPE_KIND_NONE, 0, 0, 0); }
	| CONSTEXPR { $$ = make_type_spec("constexpr", "", TYPE_KIND_NONE, 0, 0, 0); }
	| alignas_prefix constant_expression ')' {
		char *s;
		pop_state(scanner);
		safe_asprintf(&s, "alignas ( %s )", $2->text);
		$$ = make_type_spec(s, "", TYPE_KIND_NONE, 0, 0, 0);
		free(s);
		free_expr_info($2);
	}
	| alignas_prefix type_name ')' {
		char *s;
		pop_state(scanner);
		safe_asprintf(&s, "alignas ( %s )", $2.text);
		$$ = make_type_spec(s, "", TYPE_KIND_NONE, 0, 0, 0);
		free(s);
		free($2.text);
	}
	;

alignas_prefix
	: ALIGNAS { push_native_state(scanner); } '('
	;

type_name
	: specifier_qualifier_list {
		$$.simple_kind = simple_cast_kind($1, 0);
		$$.text = $1.full;
		free($1.stripped);
	}
	| specifier_qualifier_list abstract_declarator {
		$$.simple_kind = simple_cast_kind($1, 1);
		safe_asprintf(&$$.text, "%s %s", $1.full, $2);
		free($1.full);
		free($1.stripped);
		free($2);
	}
	;

type_specifier_atomic
	: TYPE_INT {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_INT, 1, 0, 0);
		free($1);
	}
	| TYPE_VOID {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_VOID, 1, 0, 0);
		free($1);
	}
	| TYPE_LONG {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_LONG, 1, 0, 0);
		free($1);
	}
	| TYPE_RUN_OBJ_T {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_RUN_OBJ_T, 1, 0, 0);
		free($1);
	}
	| STD_TYPE {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_OTHER, 1, 0, 0);
		free($1);
	}
	| TYPE_NAME { $$ = make_type_spec($1, $1, TYPE_KIND_OTHER, 1, 0, 0); free($1); }
	| struct_or_union_specifier { $$ = make_type_spec($1, $1, TYPE_KIND_OTHER, 1, 0, 1); free($1); }
	| enum_specifier { $$ = make_type_spec($1, $1, TYPE_KIND_OTHER, 1, 0, 0); free($1); }
	| TYPEOF '(' expression ')' {
		char *s;
		safe_asprintf(&s, "typeof ( %s )", $3->text);
		$$ = make_type_spec(s, s, TYPE_KIND_OTHER, 1, 0, 0);
		free(s);
		free_expr_info($3);
	}
	| TYPEOF '(' type_name ')' {
		char *s;
		safe_asprintf(&s, "typeof ( %s )", $3.text);
		$$ = make_type_spec(s, s, TYPE_KIND_OTHER, 1, 0, 0);
		free(s);
		free($3.text);
	}
	;

struct_or_union_specifier
	: struct_or_union any_id LBRACE { on_type_scope_enter(); } struct_declaration_list RBRACE { on_type_scope_exit(); safe_asprintf(&$$, "%s %s { %s }", $1, $2, $5); free($1); free($2); free($5); }
	| struct_or_union LBRACE { on_type_scope_enter(); } struct_declaration_list RBRACE { on_type_scope_exit(); safe_asprintf(&$$, "%s { %s }", $1, $4); free($1); free($4); }
	| struct_or_union any_id LBRACE { on_type_scope_enter(); on_type_scope_exit(); safe_asprintf(&$$, "%s %s { }", $1, $2); free($1); free($2); }
	| struct_or_union LBRACE { on_type_scope_enter(); on_type_scope_exit(); safe_asprintf(&$$, "%s { }", $1); free($1); }
	| struct_or_union any_id { register_type($2); safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

any_id
	: IDENTIFIER { $$ = $1; }
	| TYPE_NAME { $$ = $1; }
	| RECURSIVE_ID { $$ = $1; }
	| PRINTF { $$ = $1; }
	;

struct_or_union
	: STRUCT { $$ = strdup("struct"); }
	| UNION { $$ = strdup("union"); }
	;

struct_declaration_list
	: struct_declaration { $$ = $1; }
	| struct_declaration_list struct_declaration { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list_full ';' { safe_asprintf(&$$, "%s %s ;", $1.full, $2); free($1.full); free($1.stripped); free($2); }
	;

specifier_qualifier_list
	: specifier_qualifier { $$ = $1; }
	| specifier_qualifier_list specifier_qualifier { $$ = merge_type_specs($1, $2); }
	;

specifier_qualifier
	: type_specifier_atomic { $$ = $1; }
	| type_qualifier { $$ = $1; }
	;

struct_declarator_list_full
	: struct_declarator_full { $$ = $1; }
	| struct_declarator_list_full ',' struct_declarator_full { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	;

struct_declarator_full
	: declarator_full { $$ = $1; }
	| ':' { push_native_state(scanner); } constant_expression { pop_state(scanner); safe_asprintf(&$$, " : %s", $3->text); free_expr_info($3); }
	| declarator_full ':' { push_native_state(scanner); } constant_expression { pop_state(scanner); safe_asprintf(&$$, "%s : %s", $1, $4->text); free($1); free_expr_info($4); }
	;

enum_specifier
	: ENUM LBRACE { on_type_scope_enter(); } enumerator_list RBRACE { on_type_scope_exit(); safe_asprintf(&$$, "enum { ... }"); free($4); }
	| ENUM any_id LBRACE { on_type_scope_enter(); } enumerator_list RBRACE { on_type_scope_exit(); safe_asprintf(&$$, "enum %s { ... }", $2); free($2); free($5); }
	| ENUM any_id { register_type($2); safe_asprintf(&$$, "enum %s", $2); free($2); }
	;

enumerator_list
	: enumerator { $$ = $1; }
	| enumerator_list ',' enumerator { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	| enumerator_list ',' { $$ = $1; }
	;

enumerator
	: any_id { $$ = $1; }
	| any_id { push_native_state(scanner); } '=' constant_expression { pop_state(scanner); safe_asprintf(&$$, "%s = %s", $1, $4->text); free($1); free_expr_info($4); }
	;

type_qualifier
	: CONST { $$ = make_type_spec("const", "const", TYPE_KIND_NONE, 0, 1, 0); }
	| VOLATILE { $$ = make_type_spec("volatile", "volatile", TYPE_KIND_NONE, 0, 1, 0); }
	| RESTRICT { $$ = make_type_spec("restrict", "restrict", TYPE_KIND_NONE, 0, 1, 0); }
	| INLINE { $$ = make_type_spec("inline", "", TYPE_KIND_NONE, 0, 0, 0); }
	;

init_declarator_list_full
	: init_declarator_full { $$ = $1; }
	| init_declarator_list_full ',' init_declarator_full { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	;

init_declarator_full
	: declarator_full { $$ = $1; }
	| declarator_full '=' initializer { safe_asprintf(&$$, "%s = %s", $1, $3); free($1); free($3); }
	;

function_declarator
	: pointer direct_declarator_full {
		safe_asprintf(&$$.text, "%s %s", $1, $2);
		$$.ptr_prefix = $1;
		free($2);
	}
	| direct_declarator_full {
		$$.text = $1;
		$$.ptr_prefix = strdup("");
	}
	;

declarator_full
	: pointer direct_declarator_full { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	| direct_declarator_full { $$ = $1; }
	;



direct_declarator_full
	: any_id { on_declarator($1); $$ = $1; }
	| '(' declarator_full ')' { safe_asprintf(&$$, "( %s )", $2); free($2); }
	| direct_declarator_full '[' bracket_static_expression ']' { safe_asprintf(&$$, "%s [ %s ]", $1, $3); free($1); free($3); }
	| direct_declarator_full '[' ']' { safe_asprintf(&$$, "%s [ ]", $1); free($1); }
	| direct_declarator_full '(' { save_func_name($1); } parameter_type_list ')' { safe_asprintf(&$$, "%s ( %s )", $1, $4); free($1); free($4); }
	| direct_declarator_full '(' { save_func_name($1); } identifier_list ')' { safe_asprintf(&$$, "%s ( %s )", $1, $4); free($1); free($4); }
	| direct_declarator_full '(' ')' { save_func_name($1); safe_asprintf(&$$, "%s ( )", $1); free($1); }
	;

bracket_static_expression
	: { push_native_state(scanner); } assignment_expression { pop_state(scanner); $$ = strdup($2->text); free_expr_info($2); }
	;


pointer
	: '*' { $$ = strdup("*"); }
	| RUN_CC_MUL { $$ = strdup("*"); }
	| '*' type_qualifier_list { safe_asprintf(&$$, "* %s", $2); free($2); }
	| RUN_CC_MUL type_qualifier_list { safe_asprintf(&$$, "* %s", $2); free($2); }
	| '*' pointer { safe_asprintf(&$$, "* %s", $2); free($2); }
	| RUN_CC_MUL pointer { safe_asprintf(&$$, "* %s", $2); free($2); }
	| '*' type_qualifier_list pointer { safe_asprintf(&$$, "* %s %s", $2, $3); free($2); free($3); }
	| RUN_CC_MUL type_qualifier_list pointer { safe_asprintf(&$$, "* %s %s", $2, $3); free($2); free($3); }
	;

type_qualifier_list
	: type_qualifier { $$ = $1.full; free($1.stripped); }
	| type_qualifier_list type_qualifier { safe_asprintf(&$$, "%s %s", $1, $2.full); free($1); free($2.full); free($2.stripped); }
	;

parameter_type_list
	: parameter_list { $$ = $1; }
	| parameter_list ',' ELLIPSIS { safe_asprintf(&$$, "%s , ...", $1); free($1); }
	;

parameter_list
	: parameter_declaration { $$ = $1; }
	| parameter_list ',' parameter_declaration { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	;

parameter_declaration
	: declaration_specifiers declarator_full { safe_asprintf(&$$, "%s %s", $1.full, $2); add_param(last_id, $$, $1.stripped, $1.has_struct_union); free($1.full); free($1.stripped); free($2); }
	| declaration_specifiers abstract_declarator { safe_asprintf(&$$, "%s %s", $1.full, $2); free($1.full); free($1.stripped); free($2); }
	| declaration_specifiers { $$ = $1.full; free($1.stripped); }
	;

identifier_list
	: any_id { $$ = $1; }
	| identifier_list ',' any_id { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	;

initializer
	: assignment_expression { $$ = strdup($1->text); free_expr_info($1); }
	| LBRACE RBRACE { $$ = strdup("{ }"); }
	| LBRACE initializer_list RBRACE { safe_asprintf(&$$, "{ %s }", $2); free($2); }
	| LBRACE initializer_list ',' RBRACE { safe_asprintf(&$$, "{ %s , }", $2); free($2); }
	;

initializer_list
	: initializer { $$ = $1; }
	| designation initializer { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	| initializer_list ',' initializer { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	| initializer_list ',' designation initializer { safe_asprintf(&$$, "%s , %s %s", $1, $3, $4); free($1); free($3); free($4); }
	;

designation
	: designator_list '=' { $$ = $1; }
	;

designator_list
	: designator { $$ = $1; }
	| designator_list designator { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

designator
	: { push_native_state(scanner); } '[' constant_expression { pop_state(scanner); } ']' { safe_asprintf(&$$, "[ %s ]", $3->text); free_expr_info($3); }
	| '.' any_id { safe_asprintf(&$$, ". %s", $2); free($2); }
	;

abstract_declarator
	: pointer { $$ = $1; }
	| direct_abstract_declarator { $$ = $1; }
	| pointer direct_abstract_declarator { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { safe_asprintf(&$$, "( %s )", $2); free($2); }
	| '[' ']' { $$ = strdup("[ ]"); }
	| '[' constant_expression ']' { safe_asprintf(&$$, "[ %s ]", $2->text); free_expr_info($2); }
	| direct_abstract_declarator '[' ']' { safe_asprintf(&$$, "%s [ ]", $1); free($1); }
	| direct_abstract_declarator '[' constant_expression ']' { safe_asprintf(&$$, "%s [ %s ]", $1, $3->text); free($1); free_expr_info($3); }
	| '(' ')' { $$ = strdup("( )"); }
	| '(' parameter_type_list ')' { safe_asprintf(&$$, "( %s )", $2); free($2); }
	| direct_abstract_declarator '(' ')' { safe_asprintf(&$$, "%s ( )", $1); free($1); }
	| direct_abstract_declarator '(' parameter_type_list ')' { safe_asprintf(&$$, "%s ( %s )", $1, $3); free($1); free($3); }
	;

/* Statements */
statement_list
	: statement
	| statement_list statement
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: label statement
	| label
	;

label
	: attribute_specifier_list IDENTIFIER ':' { safe_asprintf(&$$, "%s %s :", $1, $2); print_str($$); print_str(" "); free($1); free($2); }
	| IDENTIFIER ':' { safe_asprintf(&$$, "%s :", $1); print_str($$); print_str(" "); free($1); }
	| attribute_specifier_list CASE { push_native_state(scanner); } constant_expression { pop_state(scanner); } ':' { safe_asprintf(&$$, "%s case %s :", $1, $4->text); print_str($$); print_str(" "); free($1); free_expr_info($4); }
	| CASE { push_native_state(scanner); } constant_expression { pop_state(scanner); } ':' { safe_asprintf(&$$, "case %s :", $3->text); print_str($$); print_str(" "); free_expr_info($3); }
	| attribute_specifier_list DEFAULT ':' { safe_asprintf(&$$, "%s default :", $1); print_str($$); print_str(" "); free($1); }
	| DEFAULT ':' { print_str("default : "); $$ = strdup("default :"); }
	;

compound_statement
	: LBRACE RBRACE { print_str("{ }"); }
	| LBRACE { print_str("{ "); } block_item_list RBRACE { print_str(" }"); }
	;

expression_statement
	: ';' { print_str("; "); }
	| expression ';' { print_str($1->text); print_str(" ; "); free_expr_info($1); }
	;

for_expression_opt
	: %empty { print_str(" "); }
	| expression { print_str($1->text); print_str(" "); free_expr_info($1); }
	;

for_init_clause
	: for_expression_opt
	| declaration_specifiers init_declarator_list_full { print_str($1.full); print_str(" "); print_str($2); free($1.full); free($1.stripped); free($2); }
	;

if_prefix
	: IF '(' expression ')' { start_buffering(); $$ = $3; }
	;
 
 while_prefix
 	: WHILE '(' expression ')' { start_buffering(); $$ = $3; }
 	;

for_prefix
	: FOR { start_buffering(); }
	;

selection_statement
	: if_prefix statement {
		char *stmt = stop_buffering();
		print_str("if ( "); print_str($1->text); print_str(" ) ");
		if (stmt) { print_str(stmt); free(stmt); }
		free_expr_info($1);
	}
	| if_prefix statement ELSE { start_buffering(); } statement {
		char *stmt_else = stop_buffering();
		char *stmt_if = stop_buffering();
		print_str("if ( "); print_str($1->text); print_str(" ) ");
		if (stmt_if) { print_str(stmt_if); free(stmt_if); }
		print_str(" else ");
		if (stmt_else) { print_str(stmt_else); free(stmt_else); }
		free_expr_info($1);
	}
    | IFTE '(' expression ',' expression ',' expression ')' {
        print_str("ifte ( "); print_str($3->text); print_str(" , ");
        print_str($5->text); print_str(" , "); print_str($7->text); print_str(" ) ");
        free_expr_info($3); free_expr_info($5); free_expr_info($7);
    }
    | RUN_CC_IFTE '(' expression ',' expression ',' expression ')' {
        print_str("ifte ( "); print_str($3->text); print_str(" , ");
        print_str($5->text); print_str(" , "); print_str($7->text); print_str(" ) ");
        free_expr_info($3); free_expr_info($5); free_expr_info($7);
    }
	| SWITCH '(' expression ')' { start_buffering(); } statement {
		char *stmt = stop_buffering();
		print_str("switch ( "); print_str($3->text); print_str(" ) ");
		if (stmt) { print_str(stmt); free(stmt); }
		free_expr_info($3);
	}
	;

iteration_statement
	: while_prefix statement {
		char *stmt = stop_buffering();
		print_str("while ( "); print_str($1->text); print_str(" ) ");
		if (stmt) { print_str(stmt); free(stmt); }
		free_expr_info($1);
	}
	| DO { start_buffering(); } statement WHILE '(' expression ')' ';' {
		char *stmt = stop_buffering();
		print_str("do ");
		if (stmt) { print_str(stmt); free(stmt); }
		print_str(" while ( "); print_str($6->text); print_str(" ) ; ");
		free_expr_info($6);
	}
	| for_prefix '(' for_init_clause ';' { print_str("; "); } for_expression_opt ';' { print_str("; "); } for_expression_opt ')' {
		$<str>$ = stop_buffering();
		start_buffering();
	  } statement {
		char *stmt = stop_buffering();
		print_str("for ( "); print_str($<str>11); print_str(" ) ");
		if (stmt) { print_str(stmt); free(stmt); }
		free($<str>11);
	}
	;

jump_statement
	: GOTO IDENTIFIER ';' { print_str("goto "); print_str($2); print_str(" ; "); free($2); }
	| CONTINUE ';' { print_str("continue ; "); }
	| BREAK ';' { print_str("break ; "); }
	| RETURN ';' { if (!should_emit_run()) print_str("return ; "); action_return_empty(); }
	| RETURN expression ';' { if (!should_emit_run()) { print_str("return "); print_str($2->text); print_str(" ; "); } action_return_expr($2); }
	;

/* Expressions */
generic_identifier
	: IDENTIFIER { $$ = $1; }
	| RECURSIVE_ID { $$ = $1; }
	;

recursive_call
	: RECURSIVE_ID '(' argument_expression_list ')' {
        suppress_recursive_original = 1;
		ExprInfo *e = new_recursive_call_info($1, $3->text);
		$$ = e;
		free($1); free_expr_info($3);
	}
	| RECURSIVE_ID '(' ')' {
        suppress_recursive_original = 1;
		ExprInfo *e = new_recursive_call_info($1, "");
		$$ = e;
		free($1);
	}
	;

primary_expression
	: recursive_call { $$ = $1; }
	| generic_identifier { $$ = new_expr_info($1); free($1); }
	| PRINTF {
		ExprInfo *e = new_expr_info($1);
		e->is_printf = 1;
		$$ = e;
		free($1);
	}
	| CONSTANT {
		if (run_mode && is_native_context() && !needs_run_nat && !needs_run_bool) {
			char *s;
			safe_asprintf(&s, "( %s )", $1);
			$$ = new_expr_info(s);
			free(s);
		} else {
			$$ = new_expr_info($1);
		}
		free($1);
	}
	| string_literal_sequence { $$ = new_expr_info($1); free($1); }
	| '(' expression ')' { 
		char *s; safe_asprintf(&s, "( %s )", $2->text); 
		$$ = new_expr_info(s); free(s); 
		free_expr_info($2); 
	}
	| pavlovic_operator {
			ExprInfo *e = new_expr_info($1);
			e->is_morphism = 1;
			$$ = e;
			free($1);
		}
    | OFFSETOF '(' TYPE_NAME ',' IDENTIFIER ')' {
        char *s; safe_asprintf(&s, "__builtin_offsetof ( %s , %s )", $3, $5);
        $$ = new_expr_info(s); free(s); free($3); free($5);
    }
	;

pavlovic_operator
	: RUN { $$ = $1; }
	| IDENTITY { $$ = $1; }
	| SWAP { $$ = $1; }
	| COPY { $$ = $1; }
	| DELETE { $$ = $1; }
	| SEQUENTIAL { $$ = $1; }
	| PARALLEL { $$ = $1; }
	| PARTIAL { $$ = $1; }
	;

string_literal_sequence
	: STRING_LITERAL { $$ = $1; }
	| string_literal_sequence STRING_LITERAL { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression { push_native_state(scanner); } '[' expression { pop_state(scanner); } ']' { 
		char *s; safe_asprintf(&s, "%s [ %s ]", $1->text, $4->text);
        if (should_emit_run() && $1->is_morphism) {
            $$ = reduce_axiom_string(s, scanner);
            if ($$) {
                free(s); free_expr_info($1); free_expr_info($4);
            } else {
                $$ = new_expr_info(s); free(s);
                free_expr_info($1); free_expr_info($4);
            }
        } else {
		    $$ = new_expr_info(s); free(s);
            free_expr_info($1); free_expr_info($4);
        }
	}
	| postfix_expression '(' ')' { 
		char *s; safe_asprintf(&s, "%s ( )", $1->text);
        if (should_emit_run() && $1->is_morphism) {
            $$ = reduce_axiom_string(s, scanner);
            if ($$) {
                free(s); free_expr_info($1);
            } else {
                ExprInfo *e = new_expr_info(s);
                e->is_call = 1;
                e->is_printf = $1->is_printf;
                e->func_name = strdup($1->text);
                e->args = strdup("");
                $$ = e;
                free(s);
                free_expr_info($1);
            }
        } else {
		    ExprInfo *e = new_expr_info(s);
		    e->is_call = 1;
		    e->is_printf = $1->is_printf;
		    e->func_name = strdup($1->text);
		    e->args = strdup("");
		    $$ = e;
            free(s);
            free_expr_info($1);
        }
	}

	| postfix_expression '(' argument_expression_list ')' { 
		char *args = NULL;
		const char *args_text = $3->text;
		if (should_emit_run() && $1->is_printf) {
			args = adjust_printf_args($3->text);
			if (args)
				args_text = args;
		}
		char *s; safe_asprintf(&s, "%s ( %s )", $1->text, args_text);
        if (should_emit_run() && $1->is_morphism) {
            $$ = reduce_axiom_string(s, scanner);
            if ($$) {
                free(s); free_expr_info($1); free_expr_info($3);
            } else {
                ExprInfo *e = new_expr_info(s);
                e->is_call = 1;
                e->is_printf = $1->is_printf;
                e->func_name = strdup($1->text);
                e->args = strdup(args_text);
                $$ = e;
                free(s);
                free_expr_info($1);
                free_expr_info($3);
            }
        } else {
		    ExprInfo *e = new_expr_info(s);
		    e->is_call = 1;
		    e->is_printf = $1->is_printf;
		    e->func_name = strdup($1->text);
		    e->args = strdup(args_text);
		    $$ = e;
            free(s);
            free_expr_info($1);
            free_expr_info($3);
        }
		if (args)
			free(args);
	}
	| postfix_expression '.' any_id { 
		char *s; safe_asprintf(&s, "%s . %s", $1->text, $3);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free($3);
	}
	| postfix_expression PTR_OP any_id { 
		char *s; safe_asprintf(&s, "%s -> %s", $1->text, $3);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free($3);
	}
	| postfix_expression INC_OP { 
		char *s; safe_asprintf(&s, "%s ++", $1->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1);
	}
	| postfix_expression DEC_OP { 
		char *s; safe_asprintf(&s, "%s --", $1->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1);
	}
	;

argument_expression_list
	: assignment_expression { $$ = $1; }
	| argument_expression_list ',' assignment_expression { 
		char *s; safe_asprintf(&s, "%s , %s", $1->text, $3->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free_expr_info($3);
	}
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { 
		char *s; safe_asprintf(&s, "++ %s", $2->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($2);
	}
	| DEC_OP unary_expression { 
		char *s; safe_asprintf(&s, "-- %s", $2->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($2);
	}
	| '&' cast_expression { $$ = make_op_1("&", NULL, $2); }
	| '*' cast_expression { $$ = make_op_1("*", NULL, $2); }
	| RUN_CC_MUL cast_expression { $$ = make_op_1("*", NULL, $2); }
	| '+' cast_expression { $$ = make_op_1("+", NULL, $2); }
	| RUN_CC_ADD cast_expression { $$ = make_op_1("+", NULL, $2); }
	| '-' cast_expression { $$ = make_op_1("-", "run_cc_neg", $2); }
	| RUN_CC_SUB cast_expression { $$ = make_op_1("-", "run_cc_neg", $2); }
	| '~' cast_expression { $$ = make_op_1("~", NULL, $2); }
	| '!' cast_expression { $$ = make_op_1("!", NULL, $2); }
	| RUN_CC_NOT cast_expression { $$ = make_run_bool_not($2); }
	| SIZEOF unary_expression { 
		char *s; safe_asprintf(&s, "sizeof ( %s )", $2->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($2);
	}
	| SIZEOF '(' type_name ')' { 
		char *s; safe_asprintf(&s, "sizeof ( %s )", $3.text);
		$$ = new_expr_info(s); free(s);
		free($3.text);
	}
	| ALIGNOF '(' type_name ')' { 
		char *s; safe_asprintf(&s, "alignof ( %s )", $3.text);
		$$ = new_expr_info(s); free(s);
		free($3.text);
	}
	;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression { 
		char *s;
		TypeKind ret_kind = TYPE_KIND_NONE;
		int drop_cast = 0;
		if ($4->is_call && $4->func_name)
			ret_kind = lookup_function_return_kind($4->func_name);
		if (is_native_context() &&
		    ($2.simple_kind == SIMPLE_CAST_INT ||
		     $2.simple_kind == SIMPLE_CAST_LONG) &&
		    (ret_kind == TYPE_KIND_INT || ret_kind == TYPE_KIND_LONG)) {
			drop_cast = 1;
		}

		if (should_emit_run() && $2.simple_kind != SIMPLE_CAST_NONE) {
			if ($2.simple_kind == SIMPLE_CAST_RUN_OBJ_T && run_mode) {
				safe_asprintf(&s, "( %s ) %s", $2.text, $4->text);
			} else if (is_native_context()) {
				if (drop_cast)
					safe_asprintf(&s, "%s", $4->text);
				else
					safe_asprintf(&s, "( %s ) %s", $2.text, $4->text);
			} else {
				if (verbose)
					fprintf(stderr, "DEBUG: Casting %s to nat_to_int\n", $4->text);
				needs_run_nat = 1;
				needs_run_bool = 1;
				safe_asprintf(&s, " nat_to_int ( %s ) ", $4->text);
			}
		} else {
			safe_asprintf(&s, "( %s ) %s", $2.text, $4->text);
		}
		$$ = new_expr_info(s); free(s);
		free($2.text); free_expr_info($4);
	}
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = make_op_2("*", NULL, 0, 0, $1, $3); }
	| multiplicative_expression '/' cast_expression { $$ = make_op_2("/", NULL, 0, 0, $1, $3); }
	| multiplicative_expression '%' cast_expression { $$ = make_op_2("%", NULL, 0, 0, $1, $3); }
	| multiplicative_expression RUN_CC_MUL cast_expression { $$ = make_nat_mult($1, $3); }
	| multiplicative_expression RUN_CC_DIV cast_expression { $$ = make_op_2("/", "run_cc_div", 0, 0, $1, $3); }
	| multiplicative_expression RUN_CC_MOD cast_expression { $$ = make_op_2("%", "run_cc_mod", 0, 0, $1, $3); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = make_op_2("+", NULL, 0, 0, $1, $3); }
	| additive_expression '-' multiplicative_expression { $$ = make_op_2("-", NULL, 0, 0, $1, $3); }
	| additive_expression RUN_CC_ADD multiplicative_expression { $$ = make_nat_add($1, $3); }
	| additive_expression RUN_CC_SUB multiplicative_expression { $$ = make_op_2("-", "run_cc_sub", 0, 0, $1, $3); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = make_op_2("<<", NULL, 0, 0, $1, $3); }
	| shift_expression RIGHT_OP additive_expression { $$ = make_op_2(">>", NULL, 0, 0, $1, $3); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = make_op_2("<", NULL, 0, 0, $1, $3); }
	| relational_expression '>' shift_expression { $$ = make_op_2(">", NULL, 0, 0, $1, $3); }
	| relational_expression LE_OP shift_expression { $$ = make_op_2("<=", NULL, 0, 0, $1, $3); }
	| relational_expression GE_OP shift_expression { $$ = make_op_2(">=", NULL, 0, 0, $1, $3); }
	| relational_expression RUN_CC_LT shift_expression { $$ = make_op_2("<", "run_cc_lt", 0, 0, $1, $3); }
	| relational_expression RUN_CC_GT shift_expression { $$ = make_op_2(">", "run_cc_gt", 0, 0, $1, $3); }
	| relational_expression RUN_CC_LE shift_expression { $$ = make_op_2("<=", "run_cc_le", 0, 0, $1, $3); }
	| relational_expression RUN_CC_GE shift_expression { $$ = make_op_2(">=", "run_cc_ge", 0, 0, $1, $3); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = make_op_2("==", NULL, 0, 0, $1, $3); }
	| equality_expression NE_OP relational_expression { $$ = make_op_2("!=", NULL, 0, 0, $1, $3); }
	| equality_expression RUN_CC_EQ relational_expression { $$ = make_run_iseq($1, $3); }
	| equality_expression RUN_CC_NE relational_expression { 
        ExprInfo *eq = make_run_iseq($1, $3);
        $$ = make_run_bool_not(eq);
    }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ = make_op_2("&", NULL, 0, 0, $1, $3); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ = make_op_2("^", NULL, 0, 0, $1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = make_op_2("|", NULL, 0, 0, $1, $3); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression {
		if (run_mode && is_native_context()) {
			$$ = make_op_2("&&", NULL, 0, 0, $1, $3);
		} else {
			$$ = make_op_2("&&", "run_cc_and", 0, 0, $1, $3);
		}
	}
	| logical_and_expression RUN_CC_AND inclusive_or_expression { $$ = make_op_2("&&", "run_cc_and", 0, 0, $1, $3); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression {
		if (run_mode && is_native_context()) {
			$$ = make_op_2("||", NULL, 0, 0, $1, $3);
		} else {
			$$ = make_op_2("||", "run_cc_or", 0, 0, $1, $3);
		}
	}
	| logical_or_expression RUN_CC_OR logical_and_expression { $$ = make_op_2("||", "run_cc_or", 0, 0, $1, $3); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression {
		char *s;
		if (should_emit_run()) {
			safe_asprintf(&s, "(( %s ) ? ( %s ) : ( %s ))", $1->text, $3->text, $5->text);
		} else {
			safe_asprintf(&s, "%s ? %s : %s", $1->text, $3->text, $5->text);
		}
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free_expr_info($3); free_expr_info($5);
	}
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { 
		char *s; safe_asprintf(&s, "%s %s %s", $1->text, $2, $3->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free($2); free_expr_info($3);
	}
	;

assignment_operator
	: '=' { $$ = strdup("="); }
	| MUL_ASSIGN { $$ = strdup("*="); }
	| DIV_ASSIGN { $$ = strdup("/="); }
	| MOD_ASSIGN { $$ = strdup("%="); }
	| ADD_ASSIGN { $$ = strdup("+="); }
	| SUB_ASSIGN { $$ = strdup("-="); }
	| LEFT_ASSIGN { $$ = strdup("<<="); }
	| RIGHT_ASSIGN { $$ = strdup(">>="); }
	| AND_ASSIGN { $$ = strdup("&="); }
	| XOR_ASSIGN { $$ = strdup("^="); }
	| OR_ASSIGN { $$ = strdup("|="); }
	;

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression { 
		char *s; safe_asprintf(&s, "%s , %s", $1->text, $3->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free_expr_info($3);
	}
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

/* Attributes */
attribute_specifier_list
	: attribute_specifier { $$ = $1; }
	| attribute_specifier_list attribute_specifier { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

attribute_specifier_list_opt
	: %empty { $$ = NULL; }
	| attribute_specifier_list { $$ = $1; }
	;

attribute_specifier
	: LEFT_BRACKET_BRACKET attribute_list RIGHT_BRACKET_BRACKET { safe_asprintf(&$$, "[[ %s ]]", $2); free($2); }
	;

attribute_list
	: attribute { $$ = $1; }
	| attribute_list ',' attribute { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	| attribute_list ',' { safe_asprintf(&$$, "%s , ", $1); free($1); }
	| %empty { $$ = strdup(""); }
	;

attribute
	: attribute_token attribute_argument_clause_opt { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

attribute_token
	: IDENTIFIER { $$ = $1; }
	| attribute_scoped_token { $$ = $1; }
	;

attribute_scoped_token
	: IDENTIFIER ':' ':' IDENTIFIER { safe_asprintf(&$$, "%s :: %s", $1, $4); free($1); free($4); }
	;

attribute_argument_clause_opt
	: %empty { $$ = strdup(""); }
	| '(' argument_expression_list ')' { safe_asprintf(&$$, "( %s )", $2->text); free_expr_info($2); }
	;

%%
