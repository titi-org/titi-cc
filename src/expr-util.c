#define _GNU_SOURCE
#include "cc.h"
#include "context.h"
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
