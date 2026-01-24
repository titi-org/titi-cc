#include "run_runtime.h"

run_obj_t dummy_one_arg(run_obj_t x) { return x; }
#include <stdint.h>
#include <stdio.h>

run_obj_t identity_prog(run_obj_t x) { return x; }

run_obj_t run_eval_test(run_obj_t f, run_obj_t x) {
  // This should be simplified to eval ( f , x )
  return run(program, f, x);
}

run_obj_t var_test(run_obj_t f, run_obj_t x) {
  run_obj_t v = run(program, f, x);
  return v;
}

run_obj_t eval_direct_test(run_obj_t f, run_obj_t x) {
  // This should be simplified to eval ( f , x )
  return eval(f, x);
}

run_obj_t fallback_test(run_obj_t f, run_obj_t x) {
  /* run(kleene, g, arg) should keep run(kleene, g, arg) */
  /* Cast f to correct type expected by kleene logic if needed, or just pass as
   * void* */
  /* kleene expects void* (*g)(void*, void*) */
  /* We reuse dummy_one_arg but cast it to avoid warnings if possible, or just
   * pass void* */
  return run(kleene, f, x);
}

int main() {
  run_obj_t prog = identity((run_obj_t)identity_prog);
  run_obj_t arg = 42;

  printf("run_eval_test: %ld\n", (long)run_eval_test(prog, arg));
  printf("eval_direct_test: %ld\n", (long)eval_direct_test(prog, arg));
  // printf("fallback_test: %ld\n", (long)fallback_test(prog, arg));
  /* fallback_test might crash if kleene logic is not fully robust with
     identity_prog signature mismatch (identity_prog takes 1 arg, kleene step
     takes 2). Let's skip running it, just check compilation and AST
     simplification (or lack thereof).
  */

  return 0;
}
