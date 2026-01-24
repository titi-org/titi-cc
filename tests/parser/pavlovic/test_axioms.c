#include "run_runtime.h"
#include <stdio.h>
#include <stdlib.h>

void RUN_ASSERT(int cond, const char *msg) {
  if (!cond) {
    printf("Assertion failed: %s\n", (const char *)msg);
    exit(1);
  }
}

run_obj_t f(run_obj_t x) { return x + 1; }
run_obj_t g(run_obj_t x) { return x * 2; }
run_obj_t e(run_obj_t x) { return x; }

/* Test functions to check properties */
run_obj_t test_axioms(run_obj_t x, run_obj_t y, run_obj_t a, run_obj_t c) {
  /* Basic identity axioms */
  RUN_ASSERT(compute(x) == x, "compute(x) == x");
  RUN_ASSERT(data(x) == x, "data(x) == x");
  RUN_ASSERT(identity(x) == x, "identity(x) == x");

  /* Structure axioms */
  RUN_ASSERT(swap(x, y) == x, "swap(x, y) == x");

  RUN_ASSERT(copy(x) == x, "copy(x) == x");

  RUN_ASSERT(delete(x) == 0, "delete(x) == 0");

  /* Process axioms */
  RUN_ASSERT(function(x) == x, "function(x) == x");
  RUN_ASSERT(process(x, y) == x, "process(x, y) == x");

  /* Composition */
  RUN_ASSERT(sequential(g, f, x) == x, "sequential(g, f, x) == x");

  /* Parallel */
  struct run_cc_pair p = {a, c};
  run_obj_t res = parallel(f, g, &p, 1);
  (void)res;

  /* Partial - now returns a closure, not 0 */
  run_obj_t partial_closure = partial(f, y);
  RUN_ASSERT(partial_closure != 0, "partial(f, y) creates a closure");
  struct run_cc_pair partial_args = {y, a};
  run_obj_t expected_partial = eval(f, (run_obj_t)&partial_args);
  run_obj_t evaluated_partial = eval(partial_closure, a);
  RUN_ASSERT(
      bool_value(iseq(expected_partial, evaluated_partial)),
      "eval(partial(f, y), a) == eval(f, pair(y, a))");

  /* Fixpoint */
  RUN_ASSERT(fixpoint(e) == 0, "fixpoint(e) == 0");

  /* Kleene */
  /* run_obj_t gres = kleene(g, y); */
  /* (void)gres; */

  /* Eval / Run */
  RUN_ASSERT(bool_value(iseq(eval(f, x), f(x))), "eval(f, x) == f(x)");
  RUN_ASSERT(bool_value(iseq(run(program, f, x), f(x))),
             "run(program, f, x) == f(x)");

  /* Variadic identity/idempotent */
  RUN_ASSERT(bool_value(iseq(identity(f, x), f(x))), "identity(f, x) == f(x)");
  RUN_ASSERT(bool_value(iseq(idempotent(f, x), f(x))),
             "idempotent(f, x) == f(x)");
  RUN_ASSERT(bool_value(iseq(identity(f, g, x), f(g(x)))),
             "identity(f, g, x) == f(g(x))");
  RUN_ASSERT(bool_value(iseq(idempotent(f, g, 1), f(g(1)))),
             "idempotent(f, g, 1) == f(g(1))");

  /* Equality and Decidability */
  RUN_ASSERT(bool_value(iseq(x, x)), "iseq(x, x) == true");
  RUN_ASSERT(!bool_value(iseq(x, x + 1)), "iseq(x, x+1) == false");

  /* rho(x) == x if x is a boolean projection (true or false) */
  RUN_ASSERT(bool_value(iseq(rho(RUN_BOOL_TRUE), RUN_BOOL_TRUE)),
             "rho(true) == true");

  /* Arithmetic correctness with identity embedding */
  RUN_ASSERT(bool_value(iseq(nat_add(1, 2), 3)), "nat_add(1, 2) == 3");
  RUN_ASSERT(bool_value(iseq(nat_mult(2, 3), 6)), "nat_mult(2, 3) == 6");

  printf("✓ All axioms passed successfully\n");

  return 0;
}

int main() {
  run_obj_t dummy = 1;
  test_axioms(dummy, dummy, dummy, dummy);
  return 0;
}
