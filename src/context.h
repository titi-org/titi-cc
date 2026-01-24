#ifndef RUN_CC_CONTEXT_H
#define RUN_CC_CONTEXT_H

typedef struct RunCCContext {
  char *func_name;
  int is_recursive;
  int uses_aggregate; /* Set if return type or params are struct/union */
  int ret_is_void;

  char **params;
  char **param_decls;
  char **param_types;
  int param_count;
  int param_cap;

  char *ret_type;
  char *attributes;
  int tco_arg_idx;

  struct RunCCContext *prev;
} RunCCContext;

void push_context(const char *func_name);
void push_context_from_staging(const char *func_name);
void set_context_ret_info(const char *type, int ret_is_void,
                          int ret_is_aggregate);
void set_context_attributes(const char *attrs);
void pop_context();
/* Helpers for grammar */
int is_current_func(const char *name);
void mark_recursive();
RunCCContext *get_current_context();

#endif
