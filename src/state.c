#define _POSIX_C_SOURCE 200809L
#include "cc.h"

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
