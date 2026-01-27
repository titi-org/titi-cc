#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include "parser.tab.h"
#include "cc.yy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

/* Forward declarations for val_parse wrapper */
extern int real_parse(yyscan_t scanner, val_callback_t callback);

/* Content from src/buffer.c */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

typedef struct BufferState {
  char *mem_buffer_ptr;
  size_t mem_buffer_size;
  FILE *buffer_stream;
  struct BufferState *prev;
} BufferState;

static BufferState *buffer_stack = NULL;

void start_buffering(void) {
  if (mode != MODE_C_TO_RUN)
    return;

  /* Always push a new buffer state */
  BufferState *new_state = malloc(sizeof(BufferState));
  if (!new_state) {
    perror("malloc buffer state");
    exit(1);
  }
  new_state->mem_buffer_ptr = NULL;
  new_state->mem_buffer_size = 0;
  new_state->buffer_stream =
      open_memstream(&new_state->mem_buffer_ptr, &new_state->mem_buffer_size);
  if (!new_state->buffer_stream) {
    perror("open_memstream");
    free(new_state);
    exit(1);
  }
  new_state->prev = buffer_stack;
  buffer_stack = new_state;

  suppress_print++;
}

void reset_buffer(void) {
  /* Unwind the entire stack */
  while (buffer_stack) {
    if (buffer_stack->buffer_stream)
      fclose(buffer_stack->buffer_stream);
    if (buffer_stack->mem_buffer_ptr)
      free(buffer_stack->mem_buffer_ptr);
    BufferState *prev = buffer_stack->prev;
    free(buffer_stack);
    buffer_stack = prev;
  }
  suppress_print = 0;
}

char *stop_buffering(void) {
  if (mode != MODE_C_TO_RUN)
    return NULL;

  if (suppress_print > 0) {
    suppress_print--;
  }

  /* Pop the top buffer */
  if (buffer_stack) {
    BufferState *top = buffer_stack;

    if (top->buffer_stream)
      fclose(top->buffer_stream);
    char *ret = top->mem_buffer_ptr;
    /* don't free ptr, caller owns it */

    buffer_stack = top->prev;
    free(top);

    return ret;
  }
  return NULL;
}

void append_buffer(const char *s) {
  if (buffer_stack && buffer_stack->buffer_stream) {
    fprintf(buffer_stack->buffer_stream, "%s", s);
  }
}

void print_str(const char *s) {
  if (in_discovery_pass)
    return;
  if (suppress_print > 0) {
    append_buffer(s);
  } else {
    printf("%s", s);
  }
}

void print_token(const char *t) { print_str(t); }

/* Content from src/context.c */
#define _GNU_SOURCE


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static RunCCContext *current_context = NULL;

void push_context(const char *func_name) {
  RunCCContext *ctx = (RunCCContext *)calloc(1, sizeof(RunCCContext));
  if (func_name)
    ctx->func_name = strdup(func_name);
  else
    ctx->func_name = NULL;

  ctx->is_recursive = 0;
  ctx->uses_aggregate = 0;
  ctx->ret_is_void = 0;
  ctx->params = NULL;
  ctx->param_decls = NULL;
  ctx->param_count = 0;
  ctx->param_cap = 0;
  ctx->ret_type = NULL;
  ctx->attributes = NULL;
  ctx->tco_arg_idx = 0;

  ctx->prev = current_context;
  current_context = ctx;
}

/* Staging externs from cc.h / run-cc-lex.c */
extern int staging_param_count;
extern char **staging_params;
extern char **staging_param_decls;
extern char **staging_param_types;
extern int staging_param_cap;
extern int staging_uses_aggregate;

void push_context_from_staging(const char *name) {
  push_context(name);
  RunCCContext *ctx = current_context;

  /* Transfer ownership of parameters from staging (globals) to context */
  ctx->params = staging_params;
  ctx->param_decls = staging_param_decls;
  ctx->param_types = staging_param_types;
  ctx->param_count = staging_param_count;
  ctx->param_cap = staging_param_cap;
  ctx->uses_aggregate = staging_uses_aggregate ? 1 : 0;

  /* Reset staging without freeing, since ownership moved */
  staging_params = NULL;
  staging_param_decls = NULL;
  staging_param_types = NULL;
  staging_param_count = 0;
  staging_param_cap = 0;
  staging_uses_aggregate = 0;
}

void set_context_attributes(const char *attrs) {
  if (!current_context)
    return;
  if (current_context->attributes)
    free(current_context->attributes);
  current_context->attributes = attrs ? strdup(attrs) : NULL;
}

void set_context_ret_info(const char *type, int ret_is_void,
                          int ret_is_aggregate) {
  if (!current_context)
    return;
  if (current_context->ret_type)
    free(current_context->ret_type);
  current_context->ret_type = type ? strdup(type) : NULL;
  current_context->ret_is_void = ret_is_void ? 1 : 0;
  if (ret_is_aggregate)
    current_context->uses_aggregate = 1;
}

void pop_context() {
  if (!current_context)
    return;

  RunCCContext *ctx = current_context;
  current_context = ctx->prev;

  if (ctx->func_name)
    free(ctx->func_name);
  if (ctx->ret_type)
    free(ctx->ret_type);
  if (ctx->attributes)
    free(ctx->attributes);

  if (ctx->params) {
    for (int i = 0; i < ctx->param_count; i++) {
      if (ctx->params[i])
        free(ctx->params[i]);
    }
    free(ctx->params);
  }
  if (ctx->param_decls) {
    for (int i = 0; i < ctx->param_count; i++) {
      if (ctx->param_decls[i])
        free(ctx->param_decls[i]);
    }
    free(ctx->param_decls);
  }
  if (ctx->param_types) {
    for (int i = 0; i < ctx->param_count; i++) {
      if (ctx->param_types[i])
        free(ctx->param_types[i]);
    }
    free(ctx->param_types);
  }

  free(ctx);
}

RunCCContext *get_current_context() { return current_context; }

/* Helpers for grammar */
int is_current_func(const char *name) {
  if (!current_context || !current_context->func_name || !name)
    return 0;
  return streq(name, current_context->func_name);
}

void mark_recursive() {
  if (current_context)
    current_context->is_recursive = 1;
}

/* ========== Step Function Generation (merged from transform.c) ========== */

/* Global specialized code buffer */
static char *specialized_code_buffer = NULL;
static size_t specialized_code_size = 0;

static void accumulate_specialized_code(const char *code) {
  if (!code)
    return;

  size_t code_len = strlen(code);

  specialized_code_buffer =
      realloc(specialized_code_buffer, specialized_code_size + code_len + 1);
  if (specialized_code_size == 0) {
    specialized_code_buffer[0] = '\0';
  }

  strcpy(specialized_code_buffer + specialized_code_size, code);
  specialized_code_size += code_len;
}

void emit_nested_step_full(RunCCContext *ctx, const char *body) {
  if (in_discovery_pass || !ctx || !ctx->func_name)
    return;

  const char *func_name = ctx->func_name;

  /* Emit step function signature (forward declaration) */
  char *header;
  safe_asprintf(
      &header,
      "%s run_obj_t %s_step ( run_obj_t self_void , run_obj_t %s_arg_void );\n",
      ctx->attributes ? ctx->attributes : "", func_name, func_name);
  print_str(header);
  free(header);

  safe_asprintf(&header,
                "%s run_obj_t %s_step ( run_obj_t self_void , run_obj_t "
                "%s_arg_void ) { \n "
                " run_cc_start_%s_step: ;\n",
                ctx->attributes ? ctx->attributes : "", func_name, func_name,
                func_name);
  accumulate_specialized_code(header);
  free(header);

  /* Declare self pointer for recursive call support */
  accumulate_specialized_code(
      "  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, "
      "run_obj_t))self_void;\n");
  if (ctx->param_count > 1) {
    accumulate_specialized_code("  run_obj_t run_cc_tco_args[64];\n");
  }

  /* Unpack parameters */
  if (ctx->param_count > 1) {
    for (int i = 0; i < ctx->param_count; i++) {
      char *unpack;
      safe_asprintf(&unpack,
                    "  __auto_type %s = ((run_obj_t*)%s_arg_void)[%d];\n",
                    ctx->params[i], func_name, i);
      accumulate_specialized_code(unpack);
      free(unpack);
    }
  } else if (ctx->param_count == 1) {
    char *unpack;
    safe_asprintf(&unpack, "  __auto_type %s = %s_arg_void;\n", ctx->params[0],
                  func_name);
    accumulate_specialized_code(unpack);
    free(unpack);
  }

  /* Emit body */
  if (body) {
    accumulate_specialized_code(body);
  }

  /* Add return NULL for void functions */
  const char *ret_type = ctx->ret_type ? ctx->ret_type : "void*";
  if (ctx->ret_is_void) {
    accumulate_specialized_code("  return (run_obj_t)0;\n");
  }

  accumulate_specialized_code("}\n");

  /* Emit wrapper call/return */
  const char *morphism = ctx->is_recursive ? "kleene_step" : "program_step";
  int is_void = ctx->ret_is_void;

  if (ctx->param_count > 1) {
    print_str("  run_obj_t args[] = { ");
    for (int i = 0; i < ctx->param_count; i++) {
      char *p;
      safe_asprintf(&p, "(run_obj_t)(%s)%s", ctx->params[i],
                    (i == ctx->param_count - 1) ? "" : " , ");
      print_str(p);
      free(p);
    }
    print_str(" };\n");
    char *ret;
    if (is_void) {
      safe_asprintf(&ret,
                    "  (void) run_step ( (run_obj_t)%s , (run_obj_t)%s_step , "
                    "(run_obj_t)args );\n",
                    morphism, func_name);
    } else {
      safe_asprintf(&ret,
                    "  return ((%s) run_step ( (run_obj_t)%s , "
                    "(run_obj_t)%s_step , (run_obj_t)args )) ;\n",
                    ret_type, morphism, func_name);
    }
    print_str(ret);
    free(ret);
  } else if (ctx->param_count == 1) {
    char *ret;
    if (is_void) {
      safe_asprintf(&ret,
                    "  (void) run_step ( (run_obj_t)%s , (run_obj_t)%s_step , "
                    "(run_obj_t)(%s) );\n",
                    morphism, func_name, ctx->params[0]);
    } else {
      safe_asprintf(&ret,
                    "  return ((%s) run_step ( (run_obj_t)%s , "
                    "(run_obj_t)%s_step , "
                    "(run_obj_t)(%s) )) ;\n",
                    ret_type, morphism, func_name, ctx->params[0]);
    }
    print_str(ret);
    free(ret);
  } else {
    char *ret;
    if (is_void) {
      safe_asprintf(
          &ret,
          "  (void) run_step ( (run_obj_t)%s , (run_obj_t)%s_step , 0 );\n",
          morphism, func_name);
    } else {
      safe_asprintf(&ret,
                    "  return ((%s) run_step ( (run_obj_t)%s , "
                    "(run_obj_t)%s_step , 0 )) ;\n",
                    ret_type, morphism, func_name);
    }
    print_str(ret);
    free(ret);
  }
}

void emit_all_specialized_code(void) {
  if (specialized_code_buffer && specialized_code_size > 0) {
    print_str("\n/* SPECIALIZED CODE START */\n");
    print_str(specialized_code_buffer);
    print_str("\n/* SPECIALIZED CODE END */\n");
  }
}

void reset_specialized_code(void) {
  if (specialized_code_buffer) {
    free(specialized_code_buffer);
    specialized_code_buffer = NULL;
  }
  specialized_code_size = 0;
}

/* Content from src/expr-util.c */
#define _GNU_SOURCE


#include <stdlib.h>
#include <string.h>

void free_expr_info(ExprInfo *e) {
  if (!e)
    return;
  if (e->text)
    free(e->text);
  if (e->func_name)
    free(e->func_name);
  if (e->args)
    free(e->args);
  free(e);
}

ExprInfo *new_expr_info(const char *text) {
  ExprInfo *e = malloc(sizeof(ExprInfo));
  e->text = text ? strdup(text) : NULL;
  e->is_call = 0;
  e->is_morphism = 0;
  e->is_printf = 0;
  e->is_self_call = 0;
  e->func_name = NULL;
  e->args = NULL;
  return e;
}

ExprInfo *new_recursive_call_info(const char *func, const char *args) {
  ExprInfo *e = malloc(sizeof(ExprInfo));
  e->is_call = 1;
  e->is_morphism = 0;
  e->is_printf = 0;
  e->is_self_call = 0;
  e->args = args ? strdup(args) : NULL;

  /* Handle recursive call within categorical framework */
  mark_recursive();
  if (should_emit_run()) {
    if (args && strchr(args, ',')) {
      safe_asprintf(&e->text,
                    " ( self ( (run_obj_t)self , (run_obj_t)( run_obj_t [ ] ) "
                    "{ %s } ) ) ",
                    args);
    } else {
      safe_asprintf(&e->text,
                    " ( self ( (run_obj_t)self , (run_obj_t)( ( %s ) ) ) ) ",
                    args ? args : "0");
    }
    e->func_name = strdup("self");
    e->is_self_call = 1;
  } else {
    safe_asprintf(&e->text, "%s ( %s )", func, args ? args : "");
    e->func_name = strdup(func);
  }
  return e;
}

ExprInfo *make_nat_add(ExprInfo *e1, ExprInfo *e2) {
  needs_run_nat = 1;
  needs_run_bool = 1;
  char *s;
  safe_asprintf(&s, " nat_add ( ( %s ) , ( %s ) ) ", e1->text, e2->text);
  ExprInfo *res = new_expr_info(s);
  free(s);
  free_expr_info(e1);
  free_expr_info(e2);
  return res;
}

ExprInfo *make_nat_mult(ExprInfo *e1, ExprInfo *e2) {
  needs_run_nat = 1;
  needs_run_bool = 1;
  char *s;
  safe_asprintf(&s, " nat_mult ( ( %s ) , ( %s ) ) ", e1->text, e2->text);
  ExprInfo *res = new_expr_info(s);
  free(s);
  free_expr_info(e1);
  free_expr_info(e2);
  return res;
}

ExprInfo *make_run_iseq(ExprInfo *e1, ExprInfo *e2) {
  needs_run_nat = 1;
  needs_run_bool = 1;
  char *s;
  safe_asprintf(&s, " run_iseq ( ( %s ) , ( %s ) ) ", e1->text, e2->text);
  ExprInfo *res = new_expr_info(s);
  free(s);
  free_expr_info(e1);
  free_expr_info(e2);
  return res;
}

ExprInfo *make_run_bool_not(ExprInfo *e1) {
  needs_run_bool = 1;
  char *s;
  safe_asprintf(&s, " run_bool_not ( %s ) ", e1->text);
  ExprInfo *res = new_expr_info(s);
  free(s);
  free_expr_info(e1);
  return res;
}

ExprInfo *make_generic_op(const char *op, ExprInfo *e1, ExprInfo *e2) {
  char *s;
  safe_asprintf(&s, " %s %s %s ", e1->text, op, e2->text);
  ExprInfo *res = new_expr_info(s);
  free(s);
  free_expr_info(e1);
  free_expr_info(e2);
  return res;
}

ExprInfo *make_op_1(const char *op, const char *axiom, ExprInfo *e1) {
  char *s;
  if (should_emit_run() && axiom) {
    safe_asprintf(&s, " %s %s ", op, e1->text);
  } else {
    safe_asprintf(&s, "%s %s", op, e1->text);
  }
  ExprInfo *res = new_expr_info(s);
  free(s);
  free_expr_info(e1);
  return res;
}

ExprInfo *make_op_2(const char *op, const char *axiom, int needs_nat,
                    int needs_bool, ExprInfo *e1, ExprInfo *e2) {
  char *s;
  if (axiom) {
    safe_asprintf(&s, " %s ( ( %s ) , ( %s ) ) ", axiom, e1->text, e2->text);
    if (needs_nat) {
      needs_run_nat = 1;
      needs_run_bool = 1;
    }
    if (needs_bool)
      needs_run_bool = 1;
  } else {
    safe_asprintf(&s, "%s %s %s", e1->text, op, e2->text);
  }
  ExprInfo *res = new_expr_info(s);
  free(s);
  free_expr_info(e1);
  free_expr_info(e2);
  return res;
}

/* Content from src/state.c */
#define _POSIX_C_SOURCE 200809L


/* Global state definitions */
int mode = MODE_C_TO_RUN;
int verbose = 0;
int in_discovery_pass = 0;
int in_system_header = 0;
int suppress_print = 0;
int is_typedef = 0;
int run_mode = 0;
int needs_run_nat = 0;
int needs_run_bool = 0;
int suppress_val_errors = 0;

/* Flex State constants */
int STATE_INITIAL = 0;
int STATE_PREPROC_LINE = 0;
int STATE_PREPROC_SKIP = 0;
int STATE_PAREN_SKIP = 0;

/* Parser State */
char *current_func = NULL;
char *last_id = NULL;
int id_nesting_level = 0;

/* Parameter Staging */
char **staging_params = NULL;
char **staging_param_decls = NULL;
char **staging_param_types = NULL;
int staging_param_count = 0;
int staging_param_cap = 0;
int staging_uses_aggregate = 0;
char *staging_func_name = NULL;

/* Misc */
char *filename = NULL;
int buffer_owner = 0;
int r_paren_depth = 0;

typedef struct {
  char *name;
  char *ret_type;
  TypeKind kind;
} FunctionReturnType;

static FunctionReturnType *function_return_types = NULL;
static size_t function_return_type_count = 0;
static size_t function_return_type_cap = 0;

void reset_params(void) {
  for (int i = 0; i < staging_param_count; i++) {
    free(staging_params[i]);
    free(staging_param_decls[i]);
    free(staging_param_types[i]);
  }
  staging_param_count = 0;
  staging_uses_aggregate = 0;
  if (staging_func_name) {
    free(staging_func_name);
    staging_func_name = NULL;
  }
}

void save_func_name(const char *name) {
  if (staging_func_name)
    free(staging_func_name);
  staging_func_name = strdup(name);
}

void add_param(const char *name, const char *decl, const char *type,
               int is_aggregate) {
  if (staging_param_count >= staging_param_cap) {
    int new_cap = staging_param_cap == 0 ? 16 : staging_param_cap * 2;
    staging_params = realloc(staging_params, new_cap * sizeof(char *));
    staging_param_decls =
        realloc(staging_param_decls, new_cap * sizeof(char *));
    staging_param_types =
        realloc(staging_param_types, new_cap * sizeof(char *));
    staging_param_cap = new_cap;
  }
  staging_params[staging_param_count] = strdup(name);
  staging_param_decls[staging_param_count] = strdup(decl);
  staging_param_types[staging_param_count] = strdup(type);
  staging_param_count++;
  if (is_aggregate)
    staging_uses_aggregate = 1;
}

void register_function_return_type(const char *name, const char *ret_type,
                                   TypeKind kind) {
  if (!name || !ret_type)
    return;

  for (size_t i = 0; i < function_return_type_count; i++) {
    if (streq(function_return_types[i].name, name)) {
      free(function_return_types[i].ret_type);
      function_return_types[i].ret_type = strdup(ret_type);
      function_return_types[i].kind = kind;
      return;
    }
  }

  if (function_return_type_count >= function_return_type_cap) {
    size_t new_cap = function_return_type_cap == 0
                         ? 16
                         : function_return_type_cap * 2;
    function_return_types = realloc(function_return_types,
                                     new_cap * sizeof(*function_return_types));
    function_return_type_cap = new_cap;
  }

  function_return_types[function_return_type_count].name = strdup(name);
  function_return_types[function_return_type_count].ret_type = strdup(ret_type);
  function_return_types[function_return_type_count].kind = kind;
  function_return_type_count++;
}

TypeKind lookup_function_return_kind(const char *name) {
  if (!name)
    return TYPE_KIND_NONE;
  for (size_t i = 0; i < function_return_type_count; i++) {
    if (streq(function_return_types[i].name, name))
      return function_return_types[i].kind;
  }
  return TYPE_KIND_NONE;
}

void on_function_header(const char *attrs, TypeSpecInfo spec,
                        const char *decl, const char *ptr_prefix) {
  char *type = spec.full;
  char *stripped_type = spec.stripped;
  char *full_ret_type;

  if (ptr_prefix && ptr_prefix[0]) {
    safe_asprintf(&full_ret_type, "%s %s", stripped_type, ptr_prefix);
  } else {
    full_ret_type = strdup(stripped_type);
  }

  const char *func_name = staging_func_name ? staging_func_name : last_id;
  int ret_is_void = (spec.kind == TYPE_KIND_VOID) &&
                    (!ptr_prefix || !ptr_prefix[0]);
  int ret_is_aggregate = spec.has_struct_union ? 1 : 0;
  if (func_name)
    register_function_return_type(func_name, full_ret_type, spec.kind);
  push_context_from_staging(func_name);
  set_context_ret_info(full_ret_type, ret_is_void, ret_is_aggregate);
  set_context_attributes(attrs);
  on_function_start(func_name, full_ret_type);
  free(full_ret_type);

  RunCCContext *ctx = get_current_context();
  if (attrs) {
    print_str(attrs);
    print_str(" ");
  }
  print_str(type);
  print_str(" ");
  print_str(decl);
  if (should_emit_run() && ctx && !ctx->uses_aggregate) {
    print_str(" {\n");
  }
  start_buffering();
}

void on_run_header(void) {
  push_context_from_staging("main");
  set_context_ret_info("int", 0, 0);
  on_function_start("main", "int");
  in_system_header = 0;
  start_buffering();
}

void on_function_start(const char *name, const char *ret_type) {
  if (verbose)
    fprintf(stderr, "FUNCTION START: %s (returns %s)\n", name, ret_type);
  current_func = strdup(name);
  /* Buffering already started by grammar if needed */
}

void on_declaration_end(void) {
  is_typedef = 0;
  reset_params();
}

char *on_declaration(const char *attrs, TypeSpecInfo spec,
                     const char *decl_list) {
  char *res;
  if (attrs) {
    if (decl_list) {
      safe_asprintf(&res, "%s %s %s ;", attrs, spec.full, decl_list);
    } else {
      safe_asprintf(&res, "%s %s ;", attrs, spec.full);
    }
  } else {
    if (decl_list) {
      safe_asprintf(&res, "%s %s ;", spec.full, decl_list);
    } else {
      safe_asprintf(&res, "%s ;", spec.full);
    }
  }
  return res;
}

void on_function_end(void) {
  if (verbose)
    fprintf(stderr, "FUNCTION END: %s\n", current_func);
  if (current_func) {
    free(current_func);
    current_func = NULL;
  }
}

/* Content from src/symtab.c */
#define _POSIX_C_SOURCE 200809L



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Symbol Table (Minimal for parsing C) */
char **discovered_types = NULL;
int num_discovered_types = 0;
int discovered_types_cap = 0;

int is_type(const char *name) {
  for (int i = 0; i < num_discovered_types; i++) {
    if (streq(discovered_types[i], name))
      return 1;
  }
  return 0;
}

int register_type(const char *name) {
  if (is_type(name))
    return 0;
  if (num_discovered_types >= discovered_types_cap) {
    int new_cap = discovered_types_cap == 0 ? 16 : discovered_types_cap * 2;
    char **new_arr = realloc(discovered_types, new_cap * sizeof(char *));
    if (!new_arr)
      return -1;
    discovered_types = new_arr;
    discovered_types_cap = new_cap;
  }
  if (verbose)
    fprintf(stderr, "REGISTER TYPE: %s\n", name);
  discovered_types[num_discovered_types++] = strdup(name);
  return 1;
}

int get_symbol_table_size(void) { return num_discovered_types; }

void on_storage_class_typedef(void) { is_typedef = 1; }

static int typedef_stack[32];
static int typedef_ptr = 0;

void on_type_scope_enter(void) {
  if (typedef_ptr < 32) {
    typedef_stack[typedef_ptr++] = is_typedef;
  }
  is_typedef = 0;
}

void on_type_scope_exit(void) {
  if (typedef_ptr > 0) {
    is_typedef = typedef_stack[--typedef_ptr];
  }
}

void on_declarator(const char *name) {
  if (is_typedef) {
    register_type(name);
  }
}

/* Content from src/supercompiler.c */
#define _GNU_SOURCE


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_specialized_preamble(void) {
  print_str("/* START OF run_runtime.h */\n");
  print_str("#ifndef RUN_RUNTIME_H\n");
  print_str("#define RUN_RUNTIME_H\n");
  print_str("\n");
  print_str("#include <assert.h>\n");
  print_str("#include <inttypes.h>\n");
  print_str("#include <stdarg.h>\n");
  print_str("#include <stdbool.h>\n");
  print_str("#include <stddef.h>\n");
  print_str("#include <stdint.h>\n");
  print_str("#include <stdio.h>\n");
  print_str("#include <stdlib.h>\n");
  print_str("#include <string.h>\n");
  print_str("#include <time.h>\n");
  print_str("\n");
  print_str("#if defined(__x86_64__) || defined(__i386__)\n");
  print_str("// #include <x86intrin.h>\n");
  print_str("#endif\n");
  print_str("\n");
  print_str("#ifdef __cplusplus\n");
  print_str("extern \"C\" {\n");
  print_str("#endif\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * The universal categorical object type.\n");
  print_str(" *\n");
  print_str(" * Rationale: run_obj_t is defined as intptr_t because it is the only arithmetic\n");
  print_str(" * type in C that can hold both pointers and signed integers while remaining\n");
  print_str(" * compatible with the equality '==' operator. This is essential for maintaining\n");
  print_str(" * the clean, cast-free DSL syntax in tests.\n");
  print_str(" */\n");
  print_str("typedef intptr_t run_obj_t;\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * C23 reproducible and unsequenced attributes\n");
  print_str(" */\n");
  print_str("#if defined(__GNUC__) && __GNUC__ < 14\n");
  print_str("#define RUN_REPRODUCIBLE __attribute__((pure))\n");
  print_str("#define RUN_UNSEQUENCED __attribute__((const))\n");
  print_str("#else\n");
  print_str("#define RUN_REPRODUCIBLE [[reproducible]]\n");
  print_str("#define RUN_UNSEQUENCED [[unsequenced]]\n");
  print_str("#endif\n");
  print_str("\n");
  print_str("#ifndef RUN_CC_PAIR_DEFINED\n");
  print_str("#define RUN_CC_PAIR_DEFINED\n");
  print_str("struct run_cc_pair {\n");
  print_str("  run_obj_t first;\n");
  print_str("  run_obj_t second;\n");
  print_str("};\n");
  print_str("#endif\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * Forward declarations of core functions to break circular dependencies\n");
  print_str(" */\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t(eval)(run_obj_t p, run_obj_t a);\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(data)(run_obj_t x);\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t(program)(run_obj_t f, run_obj_t y);\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t(kleene)(run_obj_t g, run_obj_t y);\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t(run)(run_obj_t p, run_obj_t x,\n");
  print_str("                                              run_obj_t a);\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t(embed)(run_obj_t a);\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t run_data_va(int count, ...);\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t partial_step(run_obj_t self,\n");
  print_str("                                                      run_obj_t args);\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * Removed variadic macro definitions.\n");
  print_str(" * All variadic forms are now handled by the compiler (val.y)\n");
  print_str(" * which desugars them into chains of binary eval/program/kleene calls.\n");
  print_str(" */\n");
  print_str("#define compute(x) (compute)((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define data(x) (data)((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define swap(x, y) (swap)((run_obj_t)(uintptr_t)(x), (run_obj_t)(uintptr_t)(y))\n");
  print_str("#define copy(x) (copy)((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define delete(x) (delete)((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define function(x) (function)((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define process(x, y)                                                          \\\n");
  print_str("  (process)((run_obj_t)(uintptr_t)(x), (run_obj_t)(uintptr_t)(y))\n");
  print_str("#define sequential(g, f, x)                                                    \\\n");
  print_str("  (sequential)((run_obj_t)(uintptr_t)(g), (run_obj_t)(uintptr_t)(f),           \\\n");
  print_str("               (run_obj_t)(uintptr_t)(x))\n");
  print_str("#define partial(f, y)                                                          \\\n");
  print_str("  (partial)((run_obj_t)(uintptr_t)(f), (run_obj_t)(uintptr_t)(y))\n");
  print_str("#define fixpoint(e) (fixpoint)((run_obj_t)(uintptr_t)(e))\n");
  print_str("#define run(p, x, a)                                                           \\\n");
  print_str("  (run)((run_obj_t)(uintptr_t)(p), (run_obj_t)(uintptr_t)(x),                  \\\n");
  print_str("        (run_obj_t)(uintptr_t)(a))\n");
  print_str("#define parallel(f, t, a, c)                                                   \\\n");
  print_str("  (parallel)((run_obj_t)(uintptr_t)(f), (run_obj_t)(uintptr_t)(t),             \\\n");
  print_str("             (run_obj_t)(uintptr_t)(a), (run_obj_t)(uintptr_t)(c))\n");
  print_str("#define eval(p, a) (eval)((run_obj_t)(uintptr_t)(p), (run_obj_t)(uintptr_t)(a))\n");
  print_str("#define program(f, y)                                                          \\\n");
  print_str("  (program)((run_obj_t)(uintptr_t)(f), (run_obj_t)(uintptr_t)(y))\n");
  print_str("#define kleene(g, y)                                                           \\\n");
  print_str("  (kleene)((run_obj_t)(uintptr_t)(g), (run_obj_t)(uintptr_t)(y))\n");
  print_str("#define identity(x) (identity)((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define idempotent(x) (idempotent)((run_obj_t)(uintptr_t)(x))\n");
  print_str("\n");
  print_str("/* C-like operator helpers used by transformed output. */\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_add(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a + (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_sub(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a - (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_mul(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a * (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_div(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a / (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_mod(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a % (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_lt(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a < (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_gt(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a > (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_le(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a <= (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_ge(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a >= (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_eq(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a == (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_ne(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a != (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_and(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a && (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_or(run_obj_t a, run_obj_t b) {\n");
  print_str("  return (run_obj_t)((intptr_t)a || (intptr_t)b);\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_cc_not(run_obj_t a) {\n");
  print_str("  return (run_obj_t)(!(intptr_t)a);\n");
  print_str("}\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * Implementations of base morphism functions\n");
  print_str(" */\n");
  print_str("\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t(run)(run_obj_t p, run_obj_t x, run_obj_t a) {\n");
  print_str("  union {\n");
  print_str("    run_obj_t (*f)(run_obj_t, run_obj_t);\n");
  print_str("    run_obj_t v;\n");
  print_str("  } cast;\n");
  print_str("  cast.v = p;\n");
  print_str("  return cast.f(x, a);\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t(program)(run_obj_t f, run_obj_t y) {\n");
  print_str("  return eval(f, y);\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t(kleene)(run_obj_t g, run_obj_t y) { return eval(g, y); }\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED\n");
  print_str("static inline run_obj_t point_step(run_obj_t self, run_obj_t args) {\n");
  print_str("  (void)args;\n");
  print_str("  return ((run_obj_t *)self)[1];\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED\n");
  print_str("static inline run_obj_t p1_step(run_obj_t self, run_obj_t args) {\n");
  print_str("  (void)self;\n");
  print_str("  struct run_cc_pair *p = (struct run_cc_pair *)args;\n");
  print_str("  return p->first;\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED\n");
  print_str("static inline run_obj_t p2_step(run_obj_t self, run_obj_t args) {\n");
  print_str("  (void)self;\n");
  print_str("  struct run_cc_pair *p = (struct run_cc_pair *)args;\n");
  print_str("  return p->second;\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t(eval)(run_obj_t p, run_obj_t a) {\n");
  print_str("  if (p == (run_obj_t)1) { /* RUN_BOOL_TRUE as first projection p1 */\n");
  print_str("    struct run_cc_pair *pair = (struct run_cc_pair *)a;\n");
  print_str("    return pair ? pair->first : (run_obj_t)0;\n");
  print_str("  }\n");
  print_str("  if (p == (run_obj_t)0) { /* RUN_BOOL_FALSE as second projection p2 */\n");
  print_str("    struct run_cc_pair *pair = (struct run_cc_pair *)a;\n");
  print_str("    return pair ? pair->second : (run_obj_t)0;\n");
  print_str("  }\n");
  print_str("  if (p > (run_obj_t)1 && p <= (run_obj_t)4096)\n");
  print_str("    return p;\n");
  print_str("\n");
  print_str("  if (p > (run_obj_t)4096) {\n");
  print_str("    /* Low-level point check: if first element is point_step, return second */\n");
  print_str("    if (((run_obj_t *)p)[0] == (run_obj_t)point_step) {\n");
  print_str("      return ((run_obj_t *)p)[1];\n");
  print_str("    }\n");
  print_str("\n");
  print_str("    /* Partial evaluator check: [partial_step, f, y] */\n");
  print_str("    if (((run_obj_t *)p)[0] == (run_obj_t)partial_step) {\n");
  print_str("      return partial_step(p, a);\n");
  print_str("    }\n");
  print_str("\n");
  print_str("    /* Morphism call: assume p is a function pointer run_obj_t (*)(run_obj_t) */\n");
  print_str("    union {\n");
  print_str("      run_obj_t (*f)(run_obj_t);\n");
  print_str("      run_obj_t v;\n");
  print_str("    } cast;\n");
  print_str("    cast.v = p;\n");
  print_str("    return cast.f(a);\n");
  print_str("  }\n");
  print_str("  return (run_obj_t)0;\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED\n");
  print_str("static inline run_obj_t run_iseq(run_obj_t p, run_obj_t q) {\n");
  print_str("  return (p == q) ? (run_obj_t)1 : (run_obj_t)0;\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t(embed)(run_obj_t a) {\n");
  print_str("  struct run_cc_pair *p =\n");
  print_str("      (struct run_cc_pair *)malloc(sizeof(struct run_cc_pair));\n");
  print_str("  p->first = (run_obj_t)point_step;\n");
  print_str("  p->second = a;\n");
  print_str("  return (run_obj_t)p;\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t run_data_va(int count, ...) {\n");
  print_str("  va_list ap;\n");
  print_str("  va_start(ap, count);\n");
  print_str("  if (count <= 0) {\n");
  print_str("    va_end(ap);\n");
  print_str("    return 0;\n");
  print_str("  }\n");
  print_str("  run_obj_t first = va_arg(ap, run_obj_t);\n");
  print_str("  if (count == 1) {\n");
  print_str("    va_end(ap);\n");
  print_str("    return first;\n");
  print_str("  }\n");
  print_str("  struct run_cc_pair *head =\n");
  print_str("      (struct run_cc_pair *)malloc(sizeof(struct run_cc_pair));\n");
  print_str("  head->first = first;\n");
  print_str("  struct run_cc_pair *curr = head;\n");
  print_str("  for (int i = 1; i < count; i++) {\n");
  print_str("    run_obj_t val = va_arg(ap, run_obj_t);\n");
  print_str("    if (i == count - 1) {\n");
  print_str("      curr->second = val;\n");
  print_str("    } else {\n");
  print_str("      struct run_cc_pair *next =\n");
  print_str("          (struct run_cc_pair *)malloc(sizeof(struct run_cc_pair));\n");
  print_str("      next->first = val;\n");
  print_str("      curr->second = (run_obj_t)next;\n");
  print_str("      curr = next;\n");
  print_str("    }\n");
  print_str("  }\n");
  print_str("  va_end(ap);\n");
  print_str("  return (run_obj_t)head;\n");
  print_str("}\n");
  print_str("\n");
  print_str("#ifndef RUN_RUNTIME_DEFS_ONLY\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(compute)(run_obj_t x) { return x; }\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(data)(run_obj_t x) { return x; }\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(identity)(run_obj_t x) { return x; }\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(idempotent)(run_obj_t x) { return x; }\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(swap)(run_obj_t x, run_obj_t y) {\n");
  print_str("  (void)y;\n");
  print_str("  return x;\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(copy)(run_obj_t x) { return x; }\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(delete)(run_obj_t x) {\n");
  print_str("  (void)x;\n");
  print_str("  return 0;\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(function)(run_obj_t x) { return x; }\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(process)(run_obj_t x, run_obj_t y) {\n");
  print_str("  (void)y;\n");
  print_str("  return x;\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(sequential)(run_obj_t g, run_obj_t f,\n");
  print_str("                                                    run_obj_t x) {\n");
  print_str("  (void)g;\n");
  print_str("  (void)f;\n");
  print_str("  return x;\n");
  print_str("}\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * Partial evaluator step function.\n");
  print_str(" * Closure structure: [partial_step, f, y]\n");
  print_str(" * When evaluated with argument a: returns eval(f, pair(y, a))\n");
  print_str(" *\n");
  print_str(" * Derived from: ⟦pev Γ y⟧ a = ⟦Γ⟧(y, a) (Section 2.2.2 of Monoidal Computer)\n");
  print_str(" */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t partial_step(run_obj_t self, run_obj_t a) {\n");
  print_str("  run_obj_t *p = (run_obj_t *)self;\n");
  print_str("  return eval(p[1], run_data_va(2, p[2], a));\n");
  print_str("}\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * partial(f, y) - Partial evaluator (pev)\n");
  print_str(" *\n");
  print_str(" * Creates a program p such that eval(p, a) = eval(f, pair(y, a))\n");
  print_str(" */\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t(partial)(run_obj_t f, run_obj_t y) {\n");
  print_str("  run_obj_t *closure = malloc(3 * sizeof(run_obj_t));\n");
  print_str("  closure[0] = (run_obj_t)partial_step;\n");
  print_str("  closure[1] = f;\n");
  print_str("  closure[2] = y;\n");
  print_str("  return (run_obj_t)closure;\n");
  print_str("}\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(fixpoint)(run_obj_t e) {\n");
  print_str("  (void)e;\n");
  print_str("  return 0;\n");
  print_str("}\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * Parallel morphism (tensor product of morphisms)\n");
  print_str(" *\n");
  print_str(" * In Pavlovic's symmetric monoidal category:\n");
  print_str(" *   f ⊗ g : A × U → B × V\n");
  print_str(" *   where f: A → B and g: U → V\n");
  print_str(" *\n");
  print_str(" * Implementation uses the symmetric swap to rearrange (f, g, a, u)\n");
  print_str(" * into ((f, a), (g, u)) then applies eval to each component.\n");
  print_str(" *\n");
  print_str(" * parallel(f, g, a, u) = (eval(f, a), eval(g, u))\n");
  print_str(" */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t(parallel)(run_obj_t f, run_obj_t g, run_obj_t a,\n");
  print_str("                                  run_obj_t u) {\n");
  print_str("  /* Conceptually: swap middle elements (f, g, a, u) -> (f, a, g, u)\n");
  print_str("   * Then apply eval to (f, a) and (g, u) */\n");
  print_str("  run_obj_t b = eval(f, a);\n");
  print_str("  run_obj_t v = eval(g, u);\n");
  print_str("  return run_data_va(2, b, v);\n");
  print_str("}\n");
  print_str("#else\n");
  print_str("#ifndef RUN_RUNTIME_DATA_DEFINED\n");
  print_str("#define RUN_RUNTIME_DATA_DEFINED\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t(data)(run_obj_t x) { return x; }\n");
  print_str("#endif\n");
  print_str("#endif\n");
  print_str("\n");
  print_str("/* Internal step function morphisms - call with (self, args) */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t run_step(run_obj_t morphism, run_obj_t step,\n");
  print_str("                                 run_obj_t args) {\n");
  print_str("  union {\n");
  print_str("    run_obj_t (*f)(run_obj_t, run_obj_t);\n");
  print_str("    run_obj_t v;\n");
  print_str("  } cast;\n");
  print_str("  cast.v = morphism;\n");
  print_str("  return cast.f(step, args);\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t program_step(run_obj_t step, run_obj_t args) {\n");
  print_str("  union {\n");
  print_str("    run_obj_t (*fn)(run_obj_t, run_obj_t);\n");
  print_str("    run_obj_t v;\n");
  print_str("  } cast;\n");
  print_str("  cast.v = step;\n");
  print_str("  return cast.fn(step, args);\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t kleene_step(run_obj_t step, run_obj_t args) {\n");
  print_str("  union {\n");
  print_str("    run_obj_t (*f)(run_obj_t, run_obj_t);\n");
  print_str("    run_obj_t v;\n");
  print_str("  } cast;\n");
  print_str("  cast.v = step;\n");
  print_str("  return cast.f(step, args);\n");
  print_str("}\n");
  print_str("\n");
  print_str("#define run_cc_constant(x) (x)\n");
  print_str("\n");
  print_str("#ifdef __cplusplus\n");
  print_str("}\n");
  print_str("#endif\n");
  print_str("\n");
  print_str("#endif /* RUN_RUNTIME_H */\n");
  print_str("/* END OF run_runtime.h */\n");
  print_str("/* START OF run_bool.h */\n");
  print_str("#ifndef RUN_BOOL_H\n");
  print_str("#define RUN_BOOL_H\n");
  print_str("\n");
  print_str("\n");
  print_str("/* Boolean constants for categorical encodings */\n");
  print_str("/* true is p1 (first projection), false is p2 (second projection) */\n");
  print_str("/* We use the numeric values 1 and 0 which eval(p, a) now interprets as p1 and\n");
  print_str(" * p2 */\n");
  print_str("#define RUN_BOOL_TRUE ((run_obj_t)1)\n");
  print_str("#define RUN_BOOL_FALSE ((run_obj_t)0)\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_bool_true(void) {\n");
  print_str("  return RUN_BOOL_TRUE;\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_bool_false(void) {\n");
  print_str("  return RUN_BOOL_FALSE;\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_bool_not(run_obj_t b) {\n");
  print_str("  /* not(b) = iif(b, false, true) = eval(b, (false, true)) */\n");
  print_str("  return eval(b, run_data_va(2, RUN_BOOL_FALSE, RUN_BOOL_TRUE));\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_bool_and(run_obj_t a, run_obj_t b) {\n");
  print_str("  /* and(a, b) = iif(a, b, false) = eval(a, (b, false)) */\n");
  print_str("  return eval(a, run_data_va(2, b, RUN_BOOL_FALSE));\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_bool_or(run_obj_t a, run_obj_t b) {\n");
  print_str("  /* or(a, b) = iif(a, true, b) = eval(a, (true, b)) */\n");
  print_str("  return eval(a, run_data_va(2, RUN_BOOL_TRUE, b));\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_bool_value(run_obj_t b) {\n");
  print_str("  /* Convert projection-based bool back to C-style 0/1 for control flow */\n");
  print_str("  return (run_obj_t)eval(b, run_data_va(2, (run_obj_t)1, (run_obj_t)0));\n");
  print_str("}\n");
  print_str("\n");
  print_str("RUN_UNSEQUENCED static inline run_obj_t run_bool(run_obj_t b) {\n");
  print_str("  return b ? RUN_BOOL_TRUE : RUN_BOOL_FALSE;\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* rho(x) = iif(iseq(x, true), true, false) */\n");
  print_str("RUN_REPRODUCIBLE static inline run_obj_t run_rho(run_obj_t x) {\n");
  print_str("  return eval(run_iseq(x, RUN_BOOL_TRUE),\n");
  print_str("              run_data_va(2, RUN_BOOL_TRUE, RUN_BOOL_FALSE));\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* Macros for cleaner syntax */\n");
  print_str("#define bool_true() run_bool_true()\n");
  print_str("#define bool_false() run_bool_false()\n");
  print_str("#define bool_not(x) run_bool_not((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define bool_and(a, b)                                                         \\\n");
  print_str("  run_bool_and((run_obj_t)(uintptr_t)(a), (run_obj_t)(uintptr_t)(b))\n");
  print_str("#define bool_or(a, b)                                                          \\\n");
  print_str("  run_bool_or((run_obj_t)(uintptr_t)(a), (run_obj_t)(uintptr_t)(b))\n");
  print_str("#define bool_value(x) run_bool_value((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define iseq(p, q)                                                             \\\n");
  print_str("  run_iseq((run_obj_t)(uintptr_t)(p), (run_obj_t)(uintptr_t)(q))\n");
  print_str("#define rho(x) run_rho((run_obj_t)(uintptr_t)(x))\n");
  print_str("\n");
  print_str("#endif /* RUN_BOOL_H */\n");
  print_str("/* END OF run_bool.h */\n");
  print_str("/* START OF run_nat.h */\n");
  print_str("#ifndef RUN_NAT_H\n");
  print_str("#define RUN_NAT_H\n");
  print_str("\n");
  print_str("\n");
  print_str("/*\n");
  print_str(" * Natural Number Formalism (Dusko/von Neumann encoding)\n");
  print_str(" *\n");
  print_str(" * Numbers are encoded as paired structures with boolean prefixes:\n");
  print_str(" *   0bar = <true, 0bar>   (self-referential fixpoint)\n");
  print_str(" *   nbar+1 = <false, nbar> (successor wraps predecessor)\n");
  print_str(" *\n");
  print_str(" * The encoding uses run_cc_pair where:\n");
  print_str(" *   - first: boolean flag (true for zero, false for successors)\n");
  print_str(" *   - second: predecessor value (or self-reference for zero)\n");
  print_str(" *\n");
  print_str(" * Operations:\n");
  print_str(" *   run_nat_zero()    - returns the representation of 0\n");
  print_str(" *   run_nat_succ(n)   - returns <false, n>\n");
  print_str(" *   run_nat_iszero(n) - returns the first component (true if 0)\n");
  print_str(" *   run_nat_pred(n)   - returns the second component (predecessor)\n");
  print_str(" *   run_nat(x)        - idempotent type filter for natural numbers\n");
  print_str(" */\n");
  print_str("\n");
  print_str("/* Boolean constants for natural number encoding */\n");
  print_str("#define RUN_NAT_TRUE RUN_BOOL_TRUE\n");
  print_str("#define RUN_NAT_FALSE RUN_BOOL_FALSE\n");
  print_str("\n");
  print_str("/* Pre-allocated zero representation (allocated on first use) */\n");
  print_str("static struct run_cc_pair *run_nat_zero_value = NULL;\n");
  print_str("\n");
  print_str("/* Initialize the zero value (lazy initialization) */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t run_nat_zero(void) {\n");
  print_str("  static run_obj_t canonical_zero = 0;\n");
  print_str("  if (canonical_zero == 0) {\n");
  print_str("    run_nat_zero_value =\n");
  print_str("        (struct run_cc_pair *)malloc(sizeof(struct run_cc_pair));\n");
  print_str("    run_nat_zero_value->first = RUN_NAT_TRUE;\n");
  print_str("    /* Fixed point: zero points to its own container */\n");
  print_str("    run_nat_zero_value->second = 0; // Temporary\n");
  print_str("    canonical_zero = embed((run_obj_t)run_nat_zero_value);\n");
  print_str("    run_nat_zero_value->second = canonical_zero; // Complete the fixpoint\n");
  print_str("  }\n");
  print_str("  return canonical_zero;\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* succ: Successor function */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t run_nat_succ(run_obj_t n) {\n");
  print_str("  return embed(run_data_va(2, RUN_NAT_FALSE, n));\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* iszero: Test if a natural number is zero */\n");
  print_str("RUN_UNSEQUENCED\n");
  print_str("static inline run_obj_t run_nat_iszero(run_obj_t n) {\n");
  print_str("  if (n == 0)\n");
  print_str("    return RUN_NAT_TRUE;\n");
  print_str("  if (n >= (run_obj_t)1 && n <= (run_obj_t)4096)\n");
  print_str("    return RUN_NAT_FALSE;\n");
  print_str("  struct run_cc_pair *p = (struct run_cc_pair *)(uintptr_t)eval(n, 0);\n");
  print_str("  return p ? p->first : RUN_NAT_FALSE;\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* pred: Predecessor function */\n");
  print_str("RUN_UNSEQUENCED\n");
  print_str("static inline run_obj_t run_nat_pred(run_obj_t n) {\n");
  print_str("  if (n == 0)\n");
  print_str("    return 0;\n");
  print_str("  if (n >= (run_obj_t)1 && n <= (run_obj_t)4096)\n");
  print_str("    return n - 1;\n");
  print_str("  struct run_cc_pair *p = (struct run_cc_pair *)(uintptr_t)eval(n, 0);\n");
  print_str("  return p ? p->second : 0;\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* run_nat: Idempotent type filter for natural numbers */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t run_nat(run_obj_t x) {\n");
  print_str("  /* Check if this is the zero representation */\n");
  print_str("  if (run_nat_iszero(x) == RUN_NAT_TRUE) {\n");
  print_str("    return x;\n");
  print_str("  }\n");
  print_str("\n");
  print_str("  /* For successors, recursively validate the predecessor */\n");
  print_str("  run_obj_t pred = run_nat_pred(x);\n");
  print_str("  run_obj_t pred_validated = run_nat(pred);\n");
  print_str("  if (pred_validated == pred) {\n");
  print_str("    return x;\n");
  print_str("  }\n");
  print_str("  return run_nat_succ(pred_validated);\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* Convert C integer to natural number representation */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t run_nat_from_int(intptr_t n) {\n");
  print_str("  if (n <= 0)\n");
  print_str("    return run_nat_zero();\n");
  print_str("  /* Safety: if n looks like a pointer, don't recurse (avoids double-wrapping\n");
  print_str("   * stack overflow) */\n");
  print_str("  if (n > 1000000)\n");
  print_str("    return (run_obj_t)n;\n");
  print_str("  return run_nat_succ(run_nat_from_int(n - 1));\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* Convert natural number representation to C integer */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline intptr_t run_nat_to_int(run_obj_t n) {\n");
  print_str("  intptr_t count = 0;\n");
  print_str("  while (run_nat_iszero(n) == RUN_NAT_FALSE) {\n");
  print_str("    count++;\n");
  print_str("    n = run_nat_pred(n);\n");
  print_str("  }\n");
  print_str("  return count;\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* add: Addition morphism (recursive structural definition) */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t run_nat_add(run_obj_t n, run_obj_t m) {\n");
  print_str("  /* if n is zero, return m */\n");
  print_str("  if (run_nat_iszero(n) == RUN_NAT_TRUE) {\n");
  print_str("    return m;\n");
  print_str("  }\n");
  print_str("  /* if n is succ(n'), return succ(add(n', m)) */\n");
  print_str("  return run_nat_succ(run_nat_add(run_nat_pred(n), m));\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* mult: Multiplication morphism */\n");
  print_str("RUN_REPRODUCIBLE\n");
  print_str("static inline run_obj_t run_nat_mult(run_obj_t n, run_obj_t m) {\n");
  print_str("  /* if n is zero, return zero */\n");
  print_str("  if (run_nat_iszero(n) == RUN_NAT_TRUE) {\n");
  print_str("    return run_nat_zero();\n");
  print_str("  }\n");
  print_str("  /* if n is succ(n'), return add(m, mult(n', m)) */\n");
  print_str("  return run_nat_add(m, run_nat_mult(run_nat_pred(n), m));\n");
  print_str("}\n");
  print_str("\n");
  print_str("/* Macros for cleaner syntax */\n");
  print_str("#define nat_zero() run_nat_zero()\n");
  print_str("#define nat_succ(n) run_nat_succ((run_obj_t)(uintptr_t)(n))\n");
  print_str("#define nat_iszero(n) run_nat_iszero((run_obj_t)(uintptr_t)(n))\n");
  print_str("#define nat_pred(n) run_nat_pred((run_obj_t)(uintptr_t)(n))\n");
  print_str("#define nat(x) run_nat((run_obj_t)(uintptr_t)(x))\n");
  print_str("#define nat_from_int(n) run_nat_from_int((intptr_t)(n))\n");
  print_str("#define nat_to_int(n) run_nat_to_int((run_obj_t)(uintptr_t)(n))\n");
  print_str("#define nat_add(n, m)                                                          \\\n");
  print_str("  run_nat_add((run_obj_t)(uintptr_t)(n), (run_obj_t)(uintptr_t)(m))\n");
  print_str("#define nat_mult(n, m)                                                         \\\n");
  print_str("  run_nat_mult((run_obj_t)(uintptr_t)(n), (run_obj_t)(uintptr_t)(m))\n");
  print_str("\n");
  print_str("#endif /* RUN_NAT_H */\n");
  print_str("/* END OF run_nat.h */\n");
}

int should_emit_run(void) {
  return (mode == MODE_C_TO_RUN || mode == MODE_DISCOVERY) && !in_system_header;
}

void action_return_empty(void) {
  if (should_emit_run()) {
    buffer_owner = 0;
    print_str("return;\n");
  }
}

void action_return_expr(ExprInfo *expr) {
  if (should_emit_run()) {
    buffer_owner = 0;

    RunCCContext *ctx = get_current_context();
    if (expr && expr->is_call && expr->is_self_call && ctx) {
      if (ctx->param_count > 1) {
        const char *p = expr->args;
        const char *arg_start = p;
        int i = 0;
        int paren_depth = 0;
        while (*p) {
          if (*p == '(')
            paren_depth++;
          else if (*p == ')')
            paren_depth--;
          else if (*p == ',' && paren_depth == 0) {
            /* Found separator */
            size_t len = p - arg_start;
            char *arg = strndup(arg_start, len);
            char *tmp;
            safe_asprintf(&tmp, "  run_cc_tco_args[%d] = (run_obj_t)( %s );\n",
                          i++, arg);
            print_str(tmp);
            free(tmp);
            free(arg);
            arg_start = p + 1;
          }
          p++;
        }
        /* Handle last argument */
        if (arg_start && *arg_start) {
          char *arg = strdup(arg_start);
          char *tmp;
          safe_asprintf(&tmp, "  run_cc_tco_args[%d] = (run_obj_t)( %s );\n",
                        i++, arg);
          print_str(tmp);
          free(tmp);
          free(arg);
        }
        char *tmp;
        safe_asprintf(&tmp, "  %s_arg_void = (run_obj_t)run_cc_tco_args;\n",
                      ctx->func_name);
        print_str(tmp);
        free(tmp);
      } else {
        char *tmp;
        safe_asprintf(&tmp, "  %s_arg_void = (run_obj_t)( %s );\n",
                      ctx->func_name, expr->args ? expr->args : "0");
        print_str(tmp);
        free(tmp);
      }
      char *tmp;
      safe_asprintf(&tmp, "  goto run_cc_start_%s_step;\n", ctx->func_name);
      print_str(tmp);
      free(tmp);
    } else if (expr && expr->text) {
      RunCCContext *ctx = get_current_context();
      if (mode == MODE_C_TO_RUN && !in_system_header && current_func &&
          !(ctx && ctx->uses_aggregate)) {
        print_str("return ( run_obj_t ) ( ");
        print_str(expr->text);
        print_str(" ) ;\n");
      } else {
        print_str("return ");
        print_str(expr->text);
        print_str(" ;\n");
      }
    } else {
      print_str("return ;\n");
    }
  }
  if (expr)
    free_expr_info(expr);
}

/* Content from src/jit.c */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

/* ArgList helpers (internal) */
static void arglist_reset(ArgList *list) {
  list->count = 0;
  list->args[0] = NULL;
}

static void arglist_add(ArgList *list, char *arg) {
  if (list->count < MAX_ARGS - 1) {
    list->args[list->count++] = arg;
    list->args[list->count] = NULL;
  } else {
    fprintf(stderr, "Error: Too many arguments\n");
    exit(1);
  }
}

static int handle_jit_run(int mem_fd, char **environ) {
#ifdef __linux__
  pid_t pid = fork();
  if (pid == 0) {
    char *args[] = {"jit_run", NULL};
    fexecve(mem_fd, args, environ);
    perror("fexecve");
    exit(1);
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
      return WEXITSTATUS(status);
    return 1;
  } else {
    perror("fork");
    return 1;
  }
#else
  (void)mem_fd;
  (void)environ;
  fprintf(stderr, "JIT run not supported on this platform.\n");
  return 1;
#endif
}

/* top_parse declared in cc.h */

static int handle_jit_compilation(const char *cc_bin, ArgList *cc_args,
                                  int *mem_fd_out) {
#ifndef __linux__
  (void)cc_bin;
  (void)cc_args;
  (void)mem_fd_out;
  fprintf(stderr, "JIT compilation not supported on this platform.\n");
  return 1;
#else
  int mem_src_fd = memfd_create("jit_source", 0);
  if (mem_src_fd == -1) {
    perror("memfd_create source");
    return 1;
  }

  int mem_bin_fd = memfd_create("jit_binary", 0);
  if (mem_bin_fd == -1) {
    perror("memfd_create binary");
    close(mem_src_fd);
    return 1;
  }

  /* Add output flag to cc_args pointing to the binary memfd */
  char *out_flag;
  safe_asprintf(&out_flag, "/proc/self/fd/%d", mem_bin_fd);
  arglist_add(cc_args, strdup("-o"));
  arglist_add(cc_args, out_flag);

  /* Redirect stdout to mem_src_fd */
  int orig_stdout = dup(STDOUT_FILENO);
  if (dup2(mem_src_fd, STDOUT_FILENO) == -1) {
    perror("dup2 mem_src_fd");
    return 1;
  }

  print_specialized_preamble();

  yyscan_t scanner;
  if (top_lex_init(&scanner)) {
    perror("yylex_init jit");
    return 1;
  }
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(filename);
    top_lex_destroy(scanner);
    return 1;
  }
  top_set_in(f, scanner);
  int res = top_parse(scanner, NULL);
  if (res == 0) {
    emit_all_specialized_code();
  }
  fclose(f);
  top_lex_destroy(scanner);
  reset_specialized_code();

  fflush(stdout);
  dup2(orig_stdout, STDOUT_FILENO);
  close(orig_stdout);

  if (res != 0) {
    fprintf(stderr, "Parser failed with code %d\n", res);
    close(mem_src_fd);
    close(mem_bin_fd);
    return res;
  }

  int pipe_src[2];
  if (pipe(pipe_src) == -1) {
    perror("pipe");
    return 1;
  }

  pid_t cc_pid = fork();
  if (cc_pid == 0) {
    close(pipe_src[1]);
    dup2(pipe_src[0], STDIN_FILENO);
    close(pipe_src[0]);

    execvp(cc_bin, cc_args->args);
    perror("execvp");
    _exit(1);
  }

  close(pipe_src[0]);
  lseek(mem_src_fd, 0, SEEK_SET);
  char buf[4096];
  ssize_t n;

  /* Debug: save to file */
  FILE *debug_f = fopen("/tmp/jit_source.c", "w");
  if (!debug_f) {
    perror("fopen /tmp/jit_source.c");
    // Continue without writing to debug file if it fails
  }

  while ((n = read(mem_src_fd, buf, sizeof(buf))) > 0) {
    if (debug_f) {
      if (fwrite(buf, 1, n, debug_f) != (size_t)n) {
        perror("fwrite to /tmp/jit_source.c");
        fclose(debug_f);
        debug_f = NULL; // Prevent further attempts to write
      }
    }
    if (write(pipe_src[1], buf, n) != n) {
      perror("write to cc");
      break;
    }
  }
  if (debug_f) {
    fclose(debug_f);
  }
  close(pipe_src[1]);

  int status_cc;
  waitpid(cc_pid, &status_cc, 0);
  int compile_res = (WIFEXITED(status_cc)) ? WEXITSTATUS(status_cc) : 1;

  if (compile_res != 0) {
    fprintf(stderr, "Compilation failed code %d\n", compile_res);
    close(mem_src_fd);
    close(mem_bin_fd);
    return 1;
  }
  close(mem_src_fd);
  *mem_fd_out = mem_bin_fd;
  return 0;
#endif
}

int jit_execute(const char *cc_bin, int argc, char **argv,
                int arg_start_index) {
  ArgList cc_args;
  arglist_reset(&cc_args);
  arglist_add(&cc_args, strdup(cc_bin));
  arglist_add(&cc_args, strdup("-x"));
  arglist_add(&cc_args, strdup("c"));
  arglist_add(&cc_args, strdup("-"));
  for (int i = arg_start_index; i < argc; i++) {
    arglist_add(&cc_args, argv[i]);
  }

  int mem_fd = -1;
  int res = handle_jit_compilation(cc_bin, &cc_args, &mem_fd);
  if (res == 0 && mem_fd != -1) {
    res = handle_jit_run(mem_fd, environ);
    close(mem_fd);
  }
  return res;
}

/* Content from src/bridge.c */

#include <stdlib.h>

#define MAX_PARK_STACK 32
static val_ptr parked_val_stack[MAX_PARK_STACK];
static int parked_val_ptr = 0;
static char *parked_str_stack[MAX_PARK_STACK];
static int parked_str_ptr = 0;

static int parked_token = -1;
static YYSTYPE parked_lval;

static int entry_marker = -1;

void set_entry_marker(int tok) { entry_marker = tok; }

void park_lookahead(int tok, YYSTYPE lval) {
  parked_token = tok;
  parked_lval = lval;
}

int bridging_lex(YYSTYPE *lvalp, yyscan_t yyscanner) {
  if (entry_marker != -1) {
    int tok = entry_marker;
    entry_marker = -1;
    *lvalp = (YYSTYPE){0};
    return tok;
  }
  if (parked_token != -1) {
    int tok = parked_token;
    *lvalp = parked_lval;
    parked_token = -1;
    return tok;
  }
  return top_lex(lvalp, yyscanner);
}

void park_val(val_ptr p) {
  if (parked_val_ptr < MAX_PARK_STACK)
    parked_val_stack[parked_val_ptr++] = p;
}
val_ptr pickup_val(void) {
  if (parked_val_ptr > 0)
    return parked_val_stack[--parked_val_ptr];
  return NULL;
}

void park_str(char *s) {
  if (parked_str_ptr < MAX_PARK_STACK)
    parked_str_stack[parked_str_ptr++] = s;
}
char *pickup_str(void) {
  if (parked_str_ptr > 0)
    return parked_str_stack[--parked_str_ptr];
  return NULL;
}

void bridge_val_cb(val_ptr p) { park_val(p); }
void bridge_str_cb(val_ptr p) { park_str((char *)p); }

/* Real Bison-generated parser */
extern int real_parse(yyscan_t scanner, val_callback_t callback);

int top_parse(yyscan_t scanner, val_callback_t callback) {
  set_active_scanner(scanner);
  set_entry_marker(START_TOP);
  return real_parse(scanner, callback);
}

int stmt_parse(yyscan_t scanner, val_callback_t callback) {
  set_active_scanner(scanner);
  set_entry_marker(START_STMT);
  return real_parse(scanner, callback);
}

int expr_parse(yyscan_t scanner, val_callback_t callback) {
  set_active_scanner(scanner);
  set_entry_marker(START_EXPR);
  return real_parse(scanner, callback);
}

int decl_parse(yyscan_t scanner, val_callback_t callback) {
  set_active_scanner(scanner);
  set_entry_marker(START_DECL);
  return real_parse(scanner, callback);
}

extern int nat_parse(yyscan_t scanner, val_callback_t callback);
extern int bool_parse(yyscan_t scanner, val_callback_t callback);
extern int val_parse(yyscan_t scanner, val_callback_t callback);

static yyscan_t active_scanner = NULL;
void set_active_scanner(yyscan_t scanner) { active_scanner = scanner; }
yyscan_t get_active_scanner(void) { return active_scanner; }

ExprInfo *reduce_axiom_string(const char *text, yyscan_t scanner) {
  (void)scanner; // Use isolated scanner
  yyscan_t temp_scanner;
  if (top_lex_init(&temp_scanner)) {
    return new_expr_info(text);
  }

  top__scan_string(text, temp_scanner);

  /* Reset bridging state for the isolated parse */
  int old_parked = parked_token;
  YYSTYPE old_parked_lval = parked_lval;
  int old_marker = entry_marker;
  char *old_last_id = last_id;
  parked_token = -1;
  entry_marker = -1;
  last_id = NULL;

  int old_suppress = suppress_val_errors;
  suppress_val_errors = 1;
  val_parse(temp_scanner, bridge_val_cb);
  suppress_val_errors = old_suppress;
  ExprInfo *res = pickup_val();

  if (last_id)
    free(last_id);
  last_id = old_last_id;

  /* Restore bridging state */
  parked_token = old_parked;
  parked_lval = old_parked_lval;
  entry_marker = old_marker;

  top_lex_destroy(temp_scanner);

  return res;
}

/* Content from src/main.c */
#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

/* External Dependencies */
extern FILE *in;
extern int lineno;
extern void restart(FILE *in);

extern int get_symbol_table_size(void);
extern int register_type(const char *name);

/*****************************************************************************/
/*                            DRIVER & HELPERS                               */
/*****************************************************************************/

typedef struct {
  const char *cc_bin;
  char *input_file;
  int ast_dump;
  int arg_index;
} Options;

static void parse_options(int argc, char **argv, Options *opts) {
  extern int top_debug;

  opts->cc_bin = getenv("RUN_CC_BIN");
  if (!opts->cc_bin)
    opts->cc_bin = "gcc";
  opts->ast_dump = 0;
  opts->input_file = NULL;

  int i = 1;
  while (i < argc && argv[i][0] == '-') {
    const char *arg = argv[i];
    if (streq(arg, "-cc") && i + 1 < argc) {
      opts->cc_bin = argv[++i];
    } else if (streq(arg, "-ast-dump")) {
      opts->ast_dump = 1;
    } else if (streq(arg, "-v")) {
      verbose = 1;
      top_debug = 1;
    } else if (streq(arg, "-R")) {
      run_mode = 1;
      /* Skip -R and its argument if present */
      if (i + 1 < argc && argv[i + 1][0] != '-')
        i++;
    }
    i++;
  }

  if (i < argc)
    opts->input_file = argv[i++];
  opts->arg_index = i;
}

int main(int argc, char **argv) {
  Options opts;
  parse_options(argc, argv, &opts);

  if (!opts.input_file) {
    fprintf(stderr, "Usage: %s [options] <input_file> [compiler_args...]\n",
            argv[0]);
    return 1;
  }

  filename = opts.input_file;

  lex_init();

  yyscan_t scanner;
  if (top_lex_init(&scanner)) {
    perror("yylex_init");
    return 1;
  }

  /* First pass: Discovery */
  mode = MODE_DISCOVERY;
  in_discovery_pass = 1;
  suppress_print = 1;
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(filename);
    return 1;
  }
  top_set_in(f, scanner);
  top_parse(scanner, NULL);
  fclose(f);

  /* Second pass: Transformation */
  mode = MODE_C_TO_RUN;
  in_discovery_pass = 0;
  suppress_print = 0;
  top_set_lineno(1, scanner);
  lex_init();
  f = fopen(filename, "r");
  if (!f) {
    perror(filename);
    return 1;
  }
  top_set_in(f, scanner);

  int final_res = 0;

  if (should_emit_run() && !opts.ast_dump) {
    /* JIT compilation and execution */
    final_res = jit_execute(opts.cc_bin, argc, argv, opts.arg_index);
  } else {
    /* Standard transformation pass for output/AST dump */
    print_specialized_preamble();
    if (top_parse(scanner, NULL) == 0) {
      emit_all_specialized_code();
    } else {
      fprintf(stderr, "Parse failed\n");
      final_res = 1;
    }
  }

  fclose(f);
  top_lex_destroy(scanner);

  return final_res;
}

/* Wrapper for val_parse to call real_parse with START_VAL */
int val_parse(yyscan_t scanner, val_callback_t callback) {
    set_active_scanner(scanner);
    set_entry_marker(START_VAL);
    int prev_mode = val_mode;
    val_mode = 1;
    int res = real_parse(scanner, callback);
    val_mode = prev_mode;
    return res;
}