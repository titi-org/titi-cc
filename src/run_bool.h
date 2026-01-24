#ifndef RUN_BOOL_H
#define RUN_BOOL_H

#include "run_runtime.h"

/* Boolean constants for categorical encodings */
/* true is p1 (first projection), false is p2 (second projection) */
/* We use the numeric values 1 and 0 which eval(p, a) now interprets as p1 and
 * p2 */
#define RUN_BOOL_TRUE ((run_obj_t)1)
#define RUN_BOOL_FALSE ((run_obj_t)0)

RUN_UNSEQUENCED static inline run_obj_t run_bool_true(void) {
  return RUN_BOOL_TRUE;
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_false(void) {
  return RUN_BOOL_FALSE;
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_not(run_obj_t b) {
  /* not(b) = iif(b, false, true) = eval(b, (false, true)) */
  return eval(b, run_data_va(2, RUN_BOOL_FALSE, RUN_BOOL_TRUE));
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_and(run_obj_t a, run_obj_t b) {
  /* and(a, b) = iif(a, b, false) = eval(a, (b, false)) */
  return eval(a, run_data_va(2, b, RUN_BOOL_FALSE));
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_or(run_obj_t a, run_obj_t b) {
  /* or(a, b) = iif(a, true, b) = eval(a, (true, b)) */
  return eval(a, run_data_va(2, RUN_BOOL_TRUE, b));
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_value(run_obj_t b) {
  /* Convert projection-based bool back to C-style 0/1 for control flow */
  return (run_obj_t)eval(b, run_data_va(2, (run_obj_t)1, (run_obj_t)0));
}

RUN_UNSEQUENCED static inline run_obj_t run_bool(run_obj_t b) {
  return b ? RUN_BOOL_TRUE : RUN_BOOL_FALSE;
}

/* rho(x) = iif(iseq(x, true), true, false) */
RUN_REPRODUCIBLE static inline run_obj_t run_rho(run_obj_t x) {
  return eval(run_iseq(x, RUN_BOOL_TRUE),
              run_data_va(2, RUN_BOOL_TRUE, RUN_BOOL_FALSE));
}

/* Macros for cleaner syntax */
#define bool_true() run_bool_true()
#define bool_false() run_bool_false()
#define bool_not(x) run_bool_not((run_obj_t)(uintptr_t)(x))
#define bool_and(a, b)                                                         \
  run_bool_and((run_obj_t)(uintptr_t)(a), (run_obj_t)(uintptr_t)(b))
#define bool_or(a, b)                                                          \
  run_bool_or((run_obj_t)(uintptr_t)(a), (run_obj_t)(uintptr_t)(b))
#define bool_value(x) run_bool_value((run_obj_t)(uintptr_t)(x))
#define iseq(p, q)                                                             \
  run_iseq((run_obj_t)(uintptr_t)(p), (run_obj_t)(uintptr_t)(q))
#define rho(x) run_rho((run_obj_t)(uintptr_t)(x))

#endif /* RUN_BOOL_H */
