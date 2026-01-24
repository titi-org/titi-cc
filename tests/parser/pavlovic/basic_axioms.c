// Test basic Pavlovic axiom operators
#include "run_runtime.h"

void *test_compute(void *x) {
  return compute(x);
}

void *test_data(void *x) {
  return data(x);
}

void *test_identity(void *x) {
  return identity(x);
}
