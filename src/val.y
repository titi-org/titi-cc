%{
#define MODULAR_PARSER
#define TOP_LEXER_SOURCE 1
#include "cc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Forward declarations to satisfy pure parser */
int val_lex(YYSTYPE *lvalp, yyscan_t yyscanner);
void val_error(yyscan_t scanner, val_callback_t callback, const char *msg);
extern int top_lex(YYSTYPE *lvalp, yyscan_t yyscanner);
char *top_get_text(yyscan_t yyscanner);

static ExprList *new_expr_list(ExprInfo *e, ExprList *n) {
    ExprList *l = malloc(sizeof(*l));
    l->expr = e;
    l->next = n;
    return l;
}

static void free_expr_list(ExprList *l) {
    while (l) {
        ExprList *next = l->next;
        if (l->expr) free_expr_info(l->expr);
        free(l);
        l = next;
    }
}

static ExprInfo *reduce_identity(ExprList *args) {
    if (!args) return NULL;
    if (!args->next) return args->expr;
    ExprInfo *rest = reduce_identity(args->next);
    char *s; safe_asprintf(&s, "eval ( data ( %s ) , %s )", args->expr->text, rest->text);
    ExprInfo *res = new_expr_info(s); free(s);
    /* We don't free args->expr here because it's owned by the list which we might free later,
       but actually we need to be careful with ownership.
       Let's say this function 'consumes' the list and its expressions. */
    free_expr_info(args->expr);
    free_expr_info(rest);
    free(args);
    return res;
}

static ExprInfo *reduce_idempotent(ExprList *args) {
    if (!args) return NULL;
    if (!args->next) return args->expr;
    ExprInfo *rest = reduce_idempotent(args->next);
    char *s; safe_asprintf(&s, "data ( eval ( %s , %s ) )", args->expr->text, rest->text);
    ExprInfo *res = new_expr_info(s); free(s);
    free_expr_info(args->expr);
    free_expr_info(rest);
    free(args);
    return res;
}

static ExprInfo *reduce_program(ExprInfo *f, ExprList *args) {
    if (!args) return f;
    ExprInfo *current = f;
    ExprList *cur_arg = args;
    while (cur_arg) {
        char *s; 
        if (current == f) {
            safe_asprintf(&s, "program ( %s , %s )", current->text, cur_arg->expr->text);
        } else {
            safe_asprintf(&s, "eval ( %s , %s )", current->text, cur_arg->expr->text);
        }
        ExprInfo *next_expr = new_expr_info(s); free(s);
        if (current != f) free_expr_info(current);
        current = next_expr;
        cur_arg = cur_arg->next;
    }
    // Note: this implementation doesn't free the original args. 
    // Usually a higher level takes care of that.
    return current;
}

static ExprInfo *reduce_kleene(ExprInfo *g, ExprList *args) {
    if (!args) return g;
    ExprInfo *current = g;
    ExprList *cur_arg = args;
    while (cur_arg) {
        char *s; 
        if (current == g) {
            safe_asprintf(&s, "kleene ( %s , %s )", current->text, cur_arg->expr->text);
        } else {
            safe_asprintf(&s, "eval ( %s , %s )", current->text, cur_arg->expr->text);
        }
        ExprInfo *next_expr = new_expr_info(s); free(s);
        if (current != g) free_expr_info(current);
        current = next_expr;
        cur_arg = cur_arg->next;
    }
    return current;
}

static ExprInfo *reduce_eval(ExprInfo *p, ExprList *args) {
    ExprInfo *current = p;
    ExprList *cur_arg = args;
    while (cur_arg) {
        char *s; safe_asprintf(&s, "eval ( %s , %s )", current->text, cur_arg->expr->text);
        ExprInfo *next_expr = new_expr_info(s); free(s);
        if (current != p) free_expr_info(current);
        current = next_expr;
        cur_arg = cur_arg->next;
    }
    return current;
}

typedef enum {
    MORPH_RUN,
    MORPH_EVAL,
    MORPH_COMPUTE,
    MORPH_PROGRAM,
    MORPH_DATA,
    MORPH_IDEMPOTENT,
    MORPH_SWAP,
    MORPH_COPY,
    MORPH_DELETE,
    MORPH_FUNCTION,
    MORPH_PROCESS,
    MORPH_SEQUENTIAL,
    MORPH_PARALLEL,
    MORPH_PARTIAL,
    MORPH_FIXPOINT,
    MORPH_KLEENE,
    MORPH_IDENTITY,
    MORPH_ISEQ,
    MORPH_RHO,
    MORPH_BOOL_VALUE,
} morphism_kind_t;

static ExprInfo *apply_generic_call(const char *name, ExprList *args) {
    char *lower_name = strdup(name);
    for (int i = 0; lower_name[i]; i++) {
        if (lower_name[i] >= 'A' && lower_name[i] <= 'Z')
            lower_name[i] = lower_name[i] + ('a' - 'A');
    }

    char *s = NULL;
    if (!args) {
        safe_asprintf(&s, "%s ( )", lower_name);
    } else {
        ExprList *cur = args;
        while (cur) {
            if (!s) {
                safe_asprintf(&s, "%s ( %s", lower_name, cur->expr->text);
            } else {
                char *old = s;
                safe_asprintf(&s, "%s , %s", old, cur->expr->text);
                free(old);
            }
            cur = cur->next;
        }
        if (s) {
            char *old = s;
            safe_asprintf(&s, "%s )", old);
            free(old);
        }
    }
    free(lower_name);

    ExprInfo *res = new_expr_info(s);
    free(s);
    free_expr_list(args);
    return res;
}

static ExprInfo *apply_morphism_kind(morphism_kind_t kind, ExprList *args) {
    if (!args) {
        return NULL;
    }

    switch (kind) {
        case MORPH_IDENTITY:
            return reduce_identity(args);
        case MORPH_IDEMPOTENT:
            return reduce_idempotent(args);
        case MORPH_PROGRAM: {
            ExprInfo *res = reduce_program(args->expr, args->next);
            free(args);
            return res;
        }
        case MORPH_KLEENE: {
            ExprInfo *res = reduce_kleene(args->expr, args->next);
            free(args);
            return res;
        }
        case MORPH_BOOL_VALUE: {
            char *s;
            safe_asprintf(&s, "run_bool_value ( %s )", args->expr->text);
            ExprInfo *res = new_expr_info(s);
            free(s);
            free_expr_list(args);
            return res;
        }
        case MORPH_ISEQ: {
            char *s;
            safe_asprintf(&s, "run_iseq ( %s , %s )", args->expr->text,
                          args->next->expr->text);
            ExprInfo *res = new_expr_info(s);
            free(s);
            free_expr_list(args);
            return res;
        }
        case MORPH_RHO: {
            char *s;
            safe_asprintf(&s, "run_rho ( %s )", args->expr->text);
            ExprInfo *res = new_expr_info(s);
            free(s);
            free_expr_list(args);
            return res;
        }
        case MORPH_EVAL: {
            ExprInfo *res = reduce_eval(args->expr, args->next);
            free(args);
            return res;
        }
        case MORPH_COMPUTE:
        case MORPH_DATA:
        case MORPH_FUNCTION: {
            ExprInfo *res = new_expr_info(args->expr->text);
            free_expr_list(args);
            return res;
        }
        case MORPH_COPY: {
            char *s;
            safe_asprintf(&s, "run_data_va ( 2 , %s , %s )", args->expr->text,
                          args->expr->text);
            ExprInfo *res = new_expr_info(s);
            free(s);
            free_expr_list(args);
            return res;
        }
        case MORPH_SWAP: {
            if (args && args->next) {
                char *s;
                safe_asprintf(&s, "run_data_va ( 2 , %s , %s )",
                              args->next->expr->text, args->expr->text);
                ExprInfo *res = new_expr_info(s);
                free(s);
                free_expr_list(args);
                return res;
            }
            break;
        }
        case MORPH_PROCESS: {
            ExprInfo *res = new_expr_info(args->expr->text);
            free_expr_list(args);
            return res;
        }
        case MORPH_DELETE: {
            ExprInfo *res = new_expr_info("0");
            free_expr_list(args);
            return res;
        }
        case MORPH_SEQUENTIAL: {
            if (args && args->next && args->next->next) {
                char *s;
                safe_asprintf(&s, "eval ( %s , eval ( %s , %s ) )",
                              args->next->expr->text, args->expr->text,
                              args->next->next->expr->text);
                ExprInfo *res = new_expr_info(s);
                free(s);
                free_expr_list(args);
                return res;
            }
            break;
        }
        case MORPH_PARTIAL: {
            if (args && args->next) {
                char *s;
                safe_asprintf(&s, "partial ( %s , %s )", args->expr->text,
                              args->next->expr->text);
                ExprInfo *res = new_expr_info(s);
                free(s);
                free_expr_list(args);
                return res;
            }
            break;
        }
        case MORPH_RUN:
            return apply_generic_call("run", args);
        case MORPH_PARALLEL:
            return apply_generic_call("parallel", args);
        case MORPH_FIXPOINT:
            return apply_generic_call("fixpoint", args);
        default:
            break;
    }

    free_expr_list(args);
    return NULL;
}
%}

%code requires {
    #include "val.h"
}

%define api.value.type {VAL_STYPE}
%define api.pure full
%define api.prefix {val_}
%lex-param { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { val_callback_t callback }

%token <str> IDENTIFIER 258
%token <str> CONSTANT 259
%token <str> STRING_LITERAL 260
%token <str> TYPE_NAME 262
%token <str> RECURSIVE_ID 264
%token <str> LE_OP 305
%token <str> GE_OP 306
%token <str> EQ_OP 307
%token <str> NE_OP 308
%token <str> AND_OP 309
%token <str> OR_OP 310
%token <str> IFTE 340
%token <str> RUN_CC_CONSTANT 1023

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
%token <str> ISEQ 362
%token <str> RHO 363
%token <str> IDENTITY 361
%token <str> BOOL_VALUE 364

%type <val> val_axiom arithmetic_axiom logic_axiom categorical_axiom
%type <list> val_list
%type <str> any_val_id
%type <morph> morphism_kind

%%

val_start:
    val_axiom { if (callback) callback($1); }
    ;

val_axiom:
    arithmetic_axiom { $$ = $1; }
  | logic_axiom { $$ = $1; }
  | categorical_axiom { $$ = $1; }
  | '(' val_axiom ')' { $$ = $2; }
  ;

arithmetic_axiom:
      '+' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) + (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
      }
    | '-' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) - (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '*' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) * (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '/' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) / (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '%' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) %% (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '&' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) & (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '|' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) | (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '^' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) ^ (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '~' '(' val_axiom ')' {
        char *s; safe_asprintf(&s, "(~(%s))", $3->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3);
    }
    | RUN_CC_CONSTANT '(' val_axiom ')' {
        char *s; safe_asprintf(&s, "(%s)", $3->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3);
    }
    ;

logic_axiom:
      '>' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) > (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
      }
    | '<' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) < (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | GE_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) >= (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | LE_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) <= (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | EQ_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) == (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | NE_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) != (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | AND_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) && (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | OR_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) || (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '!' '(' val_axiom ')' {
        char *s; safe_asprintf(&s, "(!(%s))", $3->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3);
    }
categorical_axiom:
      morphism_kind { $$ = new_expr_info($1.lexeme); free($1.lexeme); }
    | morphism_kind '(' val_list ')' { $$ = apply_morphism_kind($1.kind, $3); free($1.lexeme); }
    | morphism_kind '[' val_list ']' { $$ = apply_morphism_kind($1.kind, $3); free($1.lexeme); }
    | morphism_kind '(' ')' { $$ = new_expr_info($1.lexeme); free($1.lexeme); }
    | morphism_kind '[' ']' { $$ = new_expr_info($1.lexeme); free($1.lexeme); }
    | IFTE '(' val_axiom ',' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "ifte ( %s , %s , %s )", $3->text, $5->text, $7->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5); free_expr_info($7);
    }
    | any_val_id '(' val_list ')' { $$ = apply_generic_call($1, $3); free($1); }
    | any_val_id '[' val_list ']' { $$ = apply_generic_call($1, $3); free($1); }
    | any_val_id '(' ')' { $$ = apply_generic_call($1, NULL); free($1); }
    | any_val_id '[' ']' { $$ = apply_generic_call($1, NULL); free($1); }
    | any_val_id { $$ = new_expr_info($1); free($1); }
    | CONSTANT   { $$ = new_expr_info($1); free($1); }
    | STRING_LITERAL { $$ = new_expr_info($1); free($1); }
    ;

any_val_id:
      IDENTIFIER | TYPE_NAME | RECURSIVE_ID
    ;

morphism_kind:
      RUN { $$.kind = MORPH_RUN; $$.lexeme = $1; }
    | EVAL { $$.kind = MORPH_EVAL; $$.lexeme = $1; }
    | COMPUTE { $$.kind = MORPH_COMPUTE; $$.lexeme = $1; }
    | PROGRAM { $$.kind = MORPH_PROGRAM; $$.lexeme = $1; }
    | DATA { $$.kind = MORPH_DATA; $$.lexeme = $1; }
    | IDEMPOTENT { $$.kind = MORPH_IDEMPOTENT; $$.lexeme = $1; }
    | SWAP { $$.kind = MORPH_SWAP; $$.lexeme = $1; }
    | COPY { $$.kind = MORPH_COPY; $$.lexeme = $1; }
    | DELETE { $$.kind = MORPH_DELETE; $$.lexeme = $1; }
    | FUNCTION { $$.kind = MORPH_FUNCTION; $$.lexeme = $1; }
    | PROCESS { $$.kind = MORPH_PROCESS; $$.lexeme = $1; }
    | SEQUENTIAL { $$.kind = MORPH_SEQUENTIAL; $$.lexeme = $1; }
    | PARALLEL { $$.kind = MORPH_PARALLEL; $$.lexeme = $1; }
    | PARTIAL { $$.kind = MORPH_PARTIAL; $$.lexeme = $1; }
    | FIXPOINT { $$.kind = MORPH_FIXPOINT; $$.lexeme = $1; }
    | KLEENE { $$.kind = MORPH_KLEENE; $$.lexeme = $1; }
    | IDENTITY { $$.kind = MORPH_IDENTITY; $$.lexeme = $1; }
    | ISEQ { $$.kind = MORPH_ISEQ; $$.lexeme = $1; }
    | RHO { $$.kind = MORPH_RHO; $$.lexeme = $1; }
    | BOOL_VALUE { $$.kind = MORPH_BOOL_VALUE; $$.lexeme = $1; }
    ;

val_list:
      val_axiom { $$ = new_expr_list($1, NULL); }
    | val_axiom ',' val_list { $$ = new_expr_list($1, $3); }
    ;

%%

void val_error(yyscan_t scanner, val_callback_t callback, const char *msg) {
    (void)scanner; (void)callback;
    if (suppress_val_errors)
        return;
    fprintf(stderr, "Val Parser Error: %s at '%s'\n", msg, top_get_text(scanner));
}

int val_lex(YYSTYPE *lvalp, yyscan_t yyscanner) {
    int prev = val_mode;
    val_mode = 1;
    int tok = top_lex(lvalp, yyscanner);
    val_mode = prev;
    return tok;
}
