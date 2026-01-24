#define _GNU_SOURCE
#include "context.h"
#include "cc.h"
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
