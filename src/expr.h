#ifndef RUN_CC_EXPR_H
#define RUN_CC_EXPR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ExprInfo {
  char *text;
  int is_call;
  int is_morphism;
  int is_printf;
  int is_self_call;
  char *func_name;
  char *args;
} ExprInfo;

void free_expr_info(ExprInfo *e);
ExprInfo *new_expr_info(const char *text);
ExprInfo *new_recursive_call_info(const char *func, const char *args);

ExprInfo *make_op_1(const char *op, const char *axiom, ExprInfo *e1);
ExprInfo *make_op_2(const char *op, const char *axiom, int needs_nat,
                    int needs_bool, ExprInfo *e1, ExprInfo *e2);

#endif
