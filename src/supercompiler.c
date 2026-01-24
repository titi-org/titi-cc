#define _GNU_SOURCE
#include "cc.h"
#include "context.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_specialized_preamble(void) {
  print_str("/* PREAMBLE START */\n");
  print_str("#define __RUN_CC__ 1\n");
  print_str("#include \"run_runtime.h\"\n");
  if (needs_run_bool)
    print_str("#include \"run_bool.h\"\n");
  if (needs_run_nat)
    print_str("#include \"run_nat.h\"\n");
  print_str("/* PREAMBLE END */\n");
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
