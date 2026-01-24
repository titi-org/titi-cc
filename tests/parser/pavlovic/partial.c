// Test partial morphism
#include "run_runtime.h"

// Define a function that takes two arguments
void *f(void *x, void *y) { return nat_add(x, y); }

void *test_partial(void *y) {
  // partial(f, y) should return a function g such that g(z) = f(y, z)
  // In this case, f(y, z) = y + z
  // So we are creating a function that adds y to its argument
  return partial(f, y);
}
