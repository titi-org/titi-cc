// Test Pavlovic composition operators
#include "run_runtime.h"

void *test_sequential(void *f, void *g, void *x) {
  return sequential(f, g, x);
}

void *test_parallel(void *f, void *g, void *pair, void *n) {
  return parallel(f, g, pair, n);
}
