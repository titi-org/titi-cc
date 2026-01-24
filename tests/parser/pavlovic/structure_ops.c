// Test Pavlovic structure operators
#include "run_runtime.h"

void *test_swap(void *x, void *y) {
  return swap(x, y);
}

void *test_copy(void *x) {
  return copy(x);
}

void *test_delete(void *x) {
  return delete(x);
}
