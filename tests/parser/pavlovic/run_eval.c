// Test Pavlovic run and eval operators
#include "run_runtime.h"

void *test_eval(void *f, void *x) {
  return eval(f, x);
}

void *test_run_program(void *f, void *x) {
  return run(program, f, x);
}

void *test_run_kleene(void *f, void *x) {
  return run(kleene, f, x);
}
