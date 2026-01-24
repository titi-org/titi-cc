// Test Pavlovic process operators
#include "run_runtime.h"

void *test_function(void *x) {
  return function(x);
}

void *test_process(void *x, void *y) {
  return process(x, y);
}
