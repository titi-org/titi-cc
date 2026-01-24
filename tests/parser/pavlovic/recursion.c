// Test Pavlovic recursion operators
#include "run_runtime.h"

void *test_partial(void *f, void *x) {
  return partial(f, x);
}

void *test_fixpoint(void *f) {
  return fixpoint(f);
}

void *test_kleene(void *f, void *x) {
  return kleene(f, x);
}
