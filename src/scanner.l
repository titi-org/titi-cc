%top{
#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#define TOP_LEXER_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include "parser.tab.h"
}
%option prefix="top_"
%option reentrant bison-bridge
%option noyywrap nounput noinput yylineno
%option stack
%x COMMENT
%x PREPROC_LINE
%x PREPROC_SKIP
%x PAREN_SKIP
%s CATEGORICAL
%s NATIVE

%{
/* cc.h included via parser.tab.h */

static int native_depth = 0;
int val_mode = 0;

/* Helper macro for standard printing and returning.
 * Uses should_emit_run() to centralize mode-based dispatch logic.
 * When NOT emitting Run code (passthrough mode), tokens are printed directly.
 */
/* Helper macro for standard printing and returning. */
#define PR(tok) \
    do { \
        yylval->str = strdup(yytext); \
        if (!should_emit_run()) print_token(yytext); \
        DEBUG_PARSER(yyscanner, "TOKEN: %d (%s) STATE: %d", tok, yytext, YY_START); \
        return tok; \
    } while(0)

/* Helper for identifiers: handle logic, then print if not suppressed */
#define PR_ID() \
    do { \
        int tok; \
        yylval->str = strdup(yytext); \
        if (is_type(yytext)) { \
            tok = TYPE_NAME; \
        } else { \
            if (last_id) \
                free(last_id); \
            last_id = strdup(yytext); \
            if (is_current_func(yytext)) \
                tok = RECURSIVE_ID; \
            else \
                tok = IDENTIFIER; \
        } \
        if (!should_emit_run()) print_token(yytext); \
        DEBUG_PARSER(yyscanner, "TOKEN: %d (%s) STATE: %d", tok, yytext, YY_START); \
        return tok; \
    } while(0)

/* Helper for constants in categorical context */
#define PR_CAT_CONSTANT() \
    do { \
        yylval->str = strdup(yytext); \
        if (!should_emit_run()) print_token(yytext); \
        if (should_emit_run() && native_depth == 0) { \
            needs_run_nat = 1; \
            needs_run_bool = 1; \
        } \
        DEBUG_PARSER(yyscanner, "TOKEN: CONSTANT (%s) -> %s STATE: %d", yytext, yylval->str, YY_START); \
        return CONSTANT; \
    } while(0)

/* Helper for specialized categorical operators */
#define PR_CAT_OP(tok, axiom) \
    do { \
        yylval->str = strdup(yytext); \
        if (!should_emit_run()) print_token(yytext); \
        DEBUG_PARSER(yyscanner, "TOKEN: %d (%s) AXIOM: %s STATE: %d", tok, yytext, axiom, YY_START); \
        return tok; \
    } while(0)

/* Helper for 'return' keyword */
#define PR_RET() \
    do { \
        if (!should_emit_run()) print_token(yytext); \
        DEBUG_PARSER(yyscanner, "TOKEN: RETURN (%s)", yytext); \
        return RETURN; \
    } while(0)

void push_native_state(yyscan_t yyscanner);
void pop_state(yyscan_t yyscanner);

%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*
ID			{L}({L}|{D})*
NAT_NAME		(nat|nat_zero|nat_succ|nat_iszero|nat_pred|nat_from_int|nat_to_int|run_nat|run_nat_zero|run_nat_succ|run_nat_iszero|run_nat_pred|run_nat_from_int|run_nat_to_int|RUN_NAT_TRUE|RUN_NAT_FALSE)
BOOL_NAME		(bool|bool_true|bool_false|bool_not|bool_and|bool_or|bool_value|run_bool|run_bool_true|run_bool_false|run_bool_not|run_bool_and|run_bool_or|RUN_BOOL_TRUE|RUN_BOOL_FALSE)

STD_TYPE_CORE		("char"|"double"|"float"|"int"|"long"|"short"|"signed"|"unsigned")
STD_TYPE_MISC		("intptr_t"|"uintptr_t"|"run_obj_t"|"size_t"|"ssize_t"|"off_t"|"__builtin_va_list")
STD_TYPE_EXT		("_Bool"|"_Complex"|"_Imaginary"|"_Atomic"|"bool")
STD_TYPE_KW		({STD_TYPE_CORE}|{STD_TYPE_MISC}|{STD_TYPE_EXT})
TYPE_INT_KW		("int")
TYPE_VOID_KW		("void")
TYPE_LONG_KW		("long")
TYPE_RUN_OBJ_T_KW	("run_obj_t")
PRINTF_KW		("printf")

INLINE_KW		("inline"|"__inline__"|"__inline")
/* _Noreturn is mapped to VOLATILE for now. */
VOLATILE_KW		("volatile"|"_Noreturn")
TYPEOF_KW		("typeof"|"typeof_unqual")
ALIGNAS_KW		("alignas"|"_Alignas")
ALIGNOF_KW		("alignof"|"_Alignof")
STATIC_ASSERT_KW	("static_assert"|"_Static_assert")
THREAD_LOCAL_KW		("thread_local"|"_Thread_local")
CONSTANT_KW		("true"|"false"|"nullptr")

RUN_KW			("RUN"|"run")
EVAL_KW			("EVAL"|"eval")
COMPUTE_KW		("COMPUTE"|"compute")
PROGRAM_KW		("PROGRAM"|"program")
DATA_KW			("DATA"|"data")
IDEMPOTENT_KW		("IDEMPOTENT"|"idempotent")
FUNCTION_KW		("FUNCTION"|"function")
PROCESS_KW		("PROCESS"|"process")
FIXPOINT_KW		("FIXPOINT"|"fixpoint")
KLEENE_KW		("KLEENE"|"kleene")
ISEQ_KW			("ISEQ"|"iseq")
RHO_KW			("RHO"|"rho")
BOOL_VALUE_KW		("BOOL_VALUE"|"bool_value")


IDENTITY_KW		("IDENTITY"|"identity")
SWAP_KW			("SWAP"|"swap")
COPY_KW			("COPY"|"copy")
DELETE_KW		("DELETE"|"delete")
SEQUENTIAL_KW		("SEQUENTIAL"|"sequential")
PARALLEL_KW		("PARALLEL"|"parallel")
PARTIAL_KW      ("PARTIAL"|"partial")

MORPHISM_KW		({RUN_KW}|{IDENTITY_KW}|{SWAP_KW}|{COPY_KW}|{DELETE_KW}|{SEQUENTIAL_KW}|{PARALLEL_KW}|{PARTIAL_KW})

STRING_PREFIX		(L|u8|u|U)
STRING_LITERAL_RE	{STRING_PREFIX}?\"(\\.|[^\\"])*\"
CHAR_LITERAL_RE		{STRING_PREFIX}?'(\\.|[^\\'])+'

HEX_INT			0[xX]{H}+{IS}?
BIN_INT			0[bB][01]+{IS}?
OCT_INT			0{D}+{IS}?
DEC_INT			{D}+{IS}?
INT_CONSTANT		({HEX_INT}|{BIN_INT}|{OCT_INT}|{DEC_INT})
FLOAT_CONSTANT		({D}+{E}{FS}?|{D}*"."{D}+({E})?{FS}?|{D}+"."{D}*({E})?{FS}?)
CAT_CONSTANT_RE		({INT_CONSTANT}|{FLOAT_CONSTANT}|{CHAR_LITERAL_RE})

PR_KEYWORD_KW		({STD_TYPE_KW}|{INLINE_KW}|{VOLATILE_KW}|{TYPEOF_KW}|{ALIGNAS_KW}|{ALIGNOF_KW}|{STATIC_ASSERT_KW}|{THREAD_LOCAL_KW}|{CONSTANT_KW})
PR_CATEGORY		({PR_KEYWORD_KW}|{MORPHISM_KW})

%%

"auto"			{ PR(AUTO); }
"and"			{ PR(AND_OP); }
"and_eq"		{ PR(AND_ASSIGN); }
"bitand"		{ PR('&'); }
"bitor"			{ PR('|'); }
"break"			{ PR(BREAK); }
"case"			{ PR(CASE); }
"compl"			{ PR('~'); }
{PRINTF_KW}		{ if (val_mode) PR_ID(); else PR(PRINTF); }
{TYPE_INT_KW}		{ if (val_mode) PR_ID(); else PR(TYPE_INT); }
{TYPE_VOID_KW}		{ if (val_mode) PR_ID(); else PR(TYPE_VOID); }
{TYPE_LONG_KW}		{ if (val_mode) PR_ID(); else PR(TYPE_LONG); }
{TYPE_RUN_OBJ_T_KW}	{ if (val_mode) PR_ID(); else PR(TYPE_RUN_OBJ_T); }
{STD_TYPE_KW}		{ PR(STD_TYPE); }
"const"			{ PR(CONST); }
"continue"		{ PR(CONTINUE); }
"default"		{ PR(DEFAULT); }
"do"			{ PR(DO); }
"else"			{ PR(ELSE); }
"enum"			{ if (run_mode) { needs_run_nat = 1; needs_run_bool = 1; } PR(ENUM); }
"extern"		{ PR(EXTERN); }
"for"			{ PR(FOR); }
"goto"			{ PR(GOTO); }
"if"			{ PR(IF); }
{INLINE_KW}		{ PR(INLINE); }
"not"			{ PR('!'); }
"not_eq"		{ PR(NE_OP); }
"or"			{ PR(OR_OP); }
"or_eq"			{ PR(OR_ASSIGN); }
"register"		{ PR(REGISTER); }
"restrict"		{ PR(RESTRICT); }
"return"		{ PR_RET(); }
"sizeof"		{ PR(SIZEOF); }
"static"		{ PR(STATIC); }
"struct"		{ if (run_mode) { needs_run_nat = 1; needs_run_bool = 1; } PR(STRUCT); }
"switch"		{ if (run_mode) { needs_run_nat = 1; needs_run_bool = 1; } PR(SWITCH); }
"typedef"		{ if (run_mode) { needs_run_nat = 1; needs_run_bool = 1; } PR(TYPEDEF); }
"union"			{ if (run_mode) { needs_run_nat = 1; needs_run_bool = 1; } PR(UNION); }
"xor"			{ PR('^'); }
"xor_eq"		{ PR(XOR_ASSIGN); }
{VOLATILE_KW}		{ PR(VOLATILE); }
"while"			{ PR(WHILE); }
{TYPEOF_KW}		{ PR(TYPEOF); }
"constexpr"		{ PR(CONSTEXPR); }
{CONSTANT_KW}		{ PR(CONSTANT); }
{STATIC_ASSERT_KW}	{ PR(STATIC_ASSERT); }
{THREAD_LOCAL_KW}	{ PR(THREAD_LOCAL); }
{ALIGNAS_KW}		{ PR(ALIGNAS); }
{ALIGNOF_KW}		{ PR(ALIGNOF); }
"_Generic"		{ PR(IDENTIFIER); /* For now */ }

"ifte"       { PR(IFTE); }

 /* Dusko morphisms - both UPPERCASE (canonical) and lowercase (convenient) */
 /* Note: "run/RUN" matches both the function definition (run() {...})
    and the morphism operator (run(program, f, x)) - grammar distinguishes */
{RUN_KW}			{ PR(RUN); }
{EVAL_KW}			{ if (val_mode) PR(EVAL); else PR_ID(); }
{COMPUTE_KW}			{ if (val_mode) PR(COMPUTE); else PR_ID(); }
{PROGRAM_KW}			{ if (val_mode) PR(PROGRAM); else PR_ID(); }
{DATA_KW}			{ if (val_mode) PR(DATA); else PR_ID(); }
{IDEMPOTENT_KW}			{ if (val_mode) PR(IDEMPOTENT); else PR_ID(); }
{FUNCTION_KW}			{ if (val_mode) PR(FUNCTION); else PR_ID(); }
{PROCESS_KW}			{ if (val_mode) PR(PROCESS); else PR_ID(); }
{FIXPOINT_KW}			{ if (val_mode) PR(FIXPOINT); else PR_ID(); }
{KLEENE_KW}			{ if (val_mode) PR(KLEENE); else PR_ID(); }
{ISEQ_KW}			{ if (val_mode) PR(ISEQ); else PR_ID(); }
{RHO_KW}			{ if (val_mode) PR(RHO); else PR_ID(); }
{BOOL_VALUE_KW}			{ if (val_mode) PR(BOOL_VALUE); else PR_ID(); }
{IDENTITY_KW}			{ PR(IDENTITY); }
{SWAP_KW}			{ PR(SWAP); }
{COPY_KW}			{ PR(COPY); }
{DELETE_KW}			{ PR(DELETE); }
{SEQUENTIAL_KW}			{ PR(SEQUENTIAL); }
{PARALLEL_KW}			{ PR(PARALLEL); }
{PARTIAL_KW}            { PR(PARTIAL); }

"run_cc_add"  { PR(RUN_CC_ADD); }
"run_cc_sub"  { PR(RUN_CC_SUB); }
"run_cc_mul"  { PR(RUN_CC_MUL); }
"run_cc_div"  { PR(RUN_CC_DIV); }
"run_cc_mod"  { PR(RUN_CC_MOD); }

"run_cc_gt"   { PR(RUN_CC_GT); }
"run_cc_lt"   { PR(RUN_CC_LT); }
"run_cc_ge"   { PR(RUN_CC_GE); }
"run_cc_le"   { PR(RUN_CC_LE); }
"run_cc_eq"   { PR(RUN_CC_EQ); }
"run_cc_ne"   { PR(RUN_CC_NE); }
"run_cc_and"  { PR(RUN_CC_AND); }
"run_cc_or"   { PR(RUN_CC_OR); }
"run_cc_not"  { PR(RUN_CC_NOT); }
"run_cc_ifte" { PR(RUN_CC_IFTE); }

"run_cc_constant" { PR(RUN_CC_CONSTANT); }

{NAT_NAME}		{ needs_run_nat = 1; needs_run_bool = 1; PR_ID(); }
{BOOL_NAME}		{ needs_run_bool = 1; PR_ID(); }
{ID}			{ PR_ID(); }

{CAT_CONSTANT_RE}	{ PR_CAT_CONSTANT(); }

{STRING_LITERAL_RE}	{ PR(STRING_LITERAL); }

"..."			{ PR(ELLIPSIS); }
">>="			{ PR(RIGHT_ASSIGN); }
"<<="			{ PR(LEFT_ASSIGN); }
"+="			{ PR(ADD_ASSIGN); }
"-="			{ PR(SUB_ASSIGN); }
"*="			{ PR(MUL_ASSIGN); }
"/="			{ PR(DIV_ASSIGN); }
"%="			{ PR(MOD_ASSIGN); }
"&="			{ PR(AND_ASSIGN); }
"^="			{ PR(XOR_ASSIGN); }
"|="			{ PR(OR_ASSIGN); }
">>"			{ PR(RIGHT_OP); }
"<<"			{ PR(LEFT_OP); }
"++"			{ PR(INC_OP); }
"--"			{ PR(DEC_OP); }
"->"			{ PR(PTR_OP); }

"&&"                { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_AND, "run_cc_and"); else PR(AND_OP); }
"||"                { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_OR, "run_cc_or"); else PR(OR_OP); }
"<="                { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_LE, "run_cc_le"); else PR(LE_OP); }
">="                { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_GE, "run_cc_ge"); else PR(GE_OP); }
"=="                { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_EQ, "run_cc_eq"); else PR(EQ_OP); }
"!="                { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_NE, "run_cc_ne"); else PR(NE_OP); }
";"			{ PR(';'); }
("{"|"<%")		{ if (!should_emit_run()) print_token(yytext); return LBRACE; }
("}"|"%>")		{ if (!should_emit_run()) print_token(yytext); return RBRACE; }
","			{ PR(','); }
":"			{ PR(':'); }
"="			{ PR('='); }
"[["			{ PR(LEFT_BRACKET_BRACKET); }
"]]"			{ PR(RIGHT_BRACKET_BRACKET); }
"("			{ PR('('); }
")"			{ PR(')'); }
"["			{ PR('['); }
"]"			{ PR(']'); }
"."			{ PR('.'); }
"&"			{ PR('&'); }
"!"                 { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_NOT, "run_cc_not"); else PR('!'); }
"~"			{ PR('~'); }
"-"                 { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_SUB, "run_cc_sub"); else PR('-'); }
"+"                 { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_ADD, "run_cc_add"); else PR('+'); }
"*"                 { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_MUL, "run_cc_mul"); else PR('*'); }
"/"                 { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_DIV, "run_cc_div"); else PR('/'); }
"%"                 { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_MOD, "run_cc_mod"); else PR('%'); }
"<"                 { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_LT, "run_cc_lt"); else PR('<'); }
">"                 { if (should_emit_run() && native_depth == 0) PR_CAT_OP(RUN_CC_GT, "run_cc_gt"); else PR('>'); }
"^"			{ PR('^'); }
"|"			{ PR('|'); }
"?"			{ PR('?'); }

^"#"			{ BEGIN(PREPROC_LINE); }
<PREPROC_LINE>[ \t]*{D}+[ \t]*["]\/usr\/include\/[^"]*["]([ \t]*{D})*.* { in_system_header = 1; }
<PREPROC_LINE>[ \t]*{D}+[ \t]*["]\/usr\/lib\/[^"]*["]([ \t]*{D})*.* { in_system_header = 1; }
<PREPROC_LINE>[ \t]*{D}+[ \t]*["]\/usr\/local\/include\/[^"]*["]([ \t]*{D})*.* { in_system_header = 1; }
<PREPROC_LINE>[ \t]*{D}+[ \t]*["][^"]*lib\/gcc[^"]*["]([ \t]*{D})*.* { in_system_header = 1; }
<PREPROC_LINE>[ \t]*{D}+[ \t]*["][^"]*include-fixed[^"]*["]([ \t]*{D})*.* { in_system_header = 1; }
<PREPROC_LINE>[ \t]*{D}+[ \t]*["][^"]*["]([ \t]*{D})*.* { in_system_header = 0; }
<PREPROC_LINE>{NAT_NAME} { if (!in_system_header) { needs_run_nat = 1; needs_run_bool = 1; } }
<PREPROC_LINE>{BOOL_NAME} { if (!in_system_header) { needs_run_bool = 1; } }
<PREPROC_LINE>{ID}	{ /* ignore other identifiers */ }
<PREPROC_LINE>[^A-Za-z_\n]+ { /* ignore non-identifiers */ }
<PREPROC_LINE>\n    { BEGIN(INITIAL); print_token(yytext); }

"/*"			{ BEGIN(COMMENT); print_token(yytext); }
<COMMENT>"*/"	{ BEGIN(INITIAL); print_token(yytext); }
<COMMENT>\n		{ print_token(yytext); }
<COMMENT>.		{ print_token(yytext); }
"//"			{ BEGIN(PREPROC_SKIP); print_token(yytext); }
<PREPROC_SKIP>\n	{ BEGIN(INITIAL); print_token(yytext); }
<PREPROC_SKIP>.		{ print_token(yytext); }

[ \t\v\f]		{ print_token(yytext); }
\n              { print_token(yytext); }
.			{ /* ignore bad characters */ }

%%

/* Lexer utility functions */



#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>

void push_native_state(yyscan_t yyscanner) {
    if (verbose) fprintf(stderr, "PUSH NATIVE (top=%d)\n", yy_top_state(yyscanner));
    native_depth++;
    yy_push_state(NATIVE, yyscanner);
}

void pop_state(yyscan_t yyscanner) {
    if (verbose) fprintf(stderr, "POP STATE\n");
    if (native_depth > 0)
        native_depth--;
    yy_pop_state(yyscanner);
}

int is_native_context(void) {
    return native_depth > 0;
}

int suppress_recursive_original = 0;

void diagnostic_report(yyscan_t scanner, const char *type, const char *fmt,
                       ...) {
  if (filename)
    fprintf(stderr, "%s:%d: %s: ", filename, top_get_lineno(scanner), type);
  else
    fprintf(stderr, "unknown:%d: %s: ", top_get_lineno(scanner), type);

  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fprintf(stderr, "\n");
}

void init_states(int initial, int preproc_line, int preproc_skip,
                 int paren_skip) {
  STATE_INITIAL = initial;
  STATE_PREPROC_LINE = preproc_line;
  STATE_PREPROC_SKIP = preproc_skip;
  STATE_PAREN_SKIP = paren_skip;
}

void lex_init(void) {
  init_states(INITIAL, PREPROC_LINE, PREPROC_SKIP, PAREN_SKIP);
  in_system_header = 0;
  suppress_recursive_original = 0;
  native_depth = 0;
}

int handle_identifier(void *lvalp, const char *text) {
  REAL_STYPE *lval = (REAL_STYPE *)lvalp;
  lval->str = strdup(text);

  /* Check for type names (typedef'd identifiers) */
  if (is_type(text)) {
    return TYPE_NAME;
  }

  /* Track last identifier for declarator handling */
  if (last_id)
    free(last_id);
  last_id = strdup(text);

  /* Check for recursive function calls */
  if (is_current_func(text)) {
    return RECURSIVE_ID;
  }

  return IDENTIFIER;
}
