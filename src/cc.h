#ifndef RUN_CC_H
#define RUN_CC_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expr.h"
#include "val.h"

static inline int streq(const char *a, const char *b) {
  if (!a || !b)
    return 0;
  while (*a && *b) {
    if (*a != *b)
      return 0;
    a++;
    b++;
  }
  return *a == *b;
}

#ifndef MODULAR_PARSER
#include "parser.tab.h"
#define top_debug real_debug
extern int real_debug;
#endif

/* Include lexer header except when compiling the lexer itself */
#ifndef TOP_LEXER_SOURCE
#define YY_HEADER_EXPORT_START_CONDITIONS
#include "cc.yy.h"
#endif

/* Global State */
extern int mode;
#define MODE_DISCOVERY 0
#define MODE_C_TO_RUN 1
#define MODE_RUN_TO_C 2

extern int in_discovery_pass;
extern int verbose;
extern int lineno;
extern char *filename;
extern int val_mode;
extern int run_mode;
extern int needs_run_nat;
extern int needs_run_bool;
extern int suppress_val_errors;

/* Buffering / Suppression */
extern int suppress_print;
void start_buffering(void);
char *stop_buffering(void);
void append_buffer(const char *s);

/* Lexer Helpers */
extern char *current_func;
extern char *last_id;
extern int id_nesting_level;
extern int in_system_header;

/* Staging for Parameters */
extern char **staging_params;
extern char **staging_param_decls;
extern char **staging_param_types;
extern int staging_param_count;
extern int staging_param_cap;
extern int staging_uses_aggregate;
extern char *staging_func_name;

void reset_params(void);
void add_param(const char *name, const char *decl, const char *type,
               int is_aggregate);
void save_func_name(const char *name);
void set_func(const char *name);
void clear_func(void);

/* Lexer State IDs */
extern int STATE_INITIAL;
extern int STATE_PREPROC_LINE;
extern int STATE_PREPROC_SKIP;
extern int STATE_PAREN_SKIP;

/* Function Hooks */
void on_function_header(const char *attrs, TypeSpecInfo spec, const char *decl,
                        const char *ptr_prefix);
void on_run_header(void);
void on_function_start(const char *func_name, const char *ret_type);
void on_function_end(void);
void on_declaration_end(void);
char *on_declaration(const char *attrs, TypeSpecInfo spec,
                     const char *decl_list);
void on_storage_class_typedef(void);
void on_declarator(const char *name);
void on_type_scope_enter(void);
void on_type_scope_exit(void);
void register_function_return_type(const char *name, const char *ret_type,
                                   TypeKind kind);
TypeKind lookup_function_return_kind(const char *name);

struct RunCCContext;
void emit_nested_step_full(struct RunCCContext *ctx, const char *body);
void emit_all_specialized_code(void);
void reset_specialized_code(void);

/* JIT Hooks */
void run_jit_cleanup(void);

#define safe_asprintf(ptr, ...)                                                \
  do {                                                                         \
    if (asprintf(ptr, __VA_ARGS__) == -1) {                                    \
      fprintf(stderr, "asprintf failed\n");                                    \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

/* Type Classification */
int is_type(const char *name);
int register_type(const char *name);
int get_symbol_table_size(void);

ExprInfo *new_expr_info(const char *text);
ExprInfo *new_call_info(const char *func, const char *args);
ExprInfo *new_recursive_call_info(const char *func, const char *args);
void free_expr_info(ExprInfo *e);

/* Morphological Expression Builders */
ExprInfo *make_nat_add(ExprInfo *e1, ExprInfo *e2);
ExprInfo *make_nat_mult(ExprInfo *e1, ExprInfo *e2);
ExprInfo *make_run_iseq(ExprInfo *e1, ExprInfo *e2);
ExprInfo *make_run_bool_not(ExprInfo *e1);
ExprInfo *make_generic_op(const char *op, ExprInfo *e1, ExprInfo *e2);
ExprInfo *make_op_1(const char *op, const char *axiom, ExprInfo *e1);
ExprInfo *make_op_2(const char *op, const char *axiom, int needs_nat,
                    int needs_bool, ExprInfo *e1, ExprInfo *e2);

/* Output redirection */
void print_token(const char *t);
void print_str(const char *s);

/* ArgList for JIT (internal to jit.c) */
#define MAX_ARGS 1024
#define SCRATCH_SIZE 65536

typedef struct ArgList {
  char *args[MAX_ARGS];
  int count;
} ArgList;

/* Missing State */
extern int buffer_owner;
extern int r_paren_depth;
extern int is_typedef;
extern int suppress_recursive_original;

/* Pass-specific functions */
void action_return_empty(void);
void action_return_expr(ExprInfo *e);
int should_emit_run(void);
void reset_buffer(void);

/* Lexer internal API */
void lex_init(void);
void init_states(int initial, int preproc_line, int preproc_skip,
                 int paren_skip);
int handle_line_marker(const char *text);
int handle_identifier(void *lvalp, const char *text);
void error(const char *s);
void push_native_state(yyscan_t yyscanner);
void pop_state(yyscan_t yyscanner);
int is_native_context(void);

/* Diagnostic Helpers */
void diagnostic_report(yyscan_t scanner, const char *type, const char *fmt,
                       ...);

#define DEBUG_PARSER(scanner, ...)                                             \
  if (verbose > 1)                                                             \
  diagnostic_report(scanner, "DEBUG", __VA_ARGS__)

#define PARSER_ERROR(scanner, ...)                                             \
  diagnostic_report(scanner, "error", __VA_ARGS__)

#define LEXER_ERROR(scanner, ...)                                              \
  diagnostic_report(scanner, "lexer error", __VA_ARGS__)

#define PARSER_RECOVER(scanner, ...)                                           \
  if (verbose)                                                                 \
  diagnostic_report(scanner, "recovery", __VA_ARGS__)

/* Reentrant Helpers - use top_* directly from cc.yy.h */
void park_lookahead(int tok, YYSTYPE lval);
int bridging_lex(YYSTYPE *lvalp, yyscan_t yyscanner);
ExprInfo *reduce_axiom_string(const char *text, yyscan_t scanner);
void set_active_scanner(yyscan_t scanner);
yyscan_t get_active_scanner(void);

/* Exported Parser Entry Points */
int top_parse(yyscan_t scanner, val_callback_t callback);
int expr_parse(yyscan_t scanner, val_callback_t callback);
int decl_parse(yyscan_t scanner, val_callback_t callback);
int stmt_parse(yyscan_t scanner, val_callback_t callback);
int nat_parse(yyscan_t scanner, val_callback_t callback);
int bool_parse(yyscan_t scanner, val_callback_t callback);

/* JIT driver */
extern char **environ;
int jit_execute(const char *cc_bin, int argc, char **argv, int arg_start_index);

/* Specialized code */
void print_specialized_preamble(void);

#endif
