// Consolidated regression tests for grammar parsing
// This file combines all repro_*.c test cases

#include <stdint.h>
#include <stdio.h>

// Test 1: Simple variable declaration
int global_int = 0;
uintptr_t global_uintptr = 0;

// Test 2: Cast with primitive type (no typedef)
int test_cast_int(int x) { return (int)x; }

// Test 3: Cast inside function body with typedef
typedef int mytype;
int test_cast_typedef(int x) { return (mytype)x; }

// Test 4: Simple uintptr_t cast
uintptr_t test_simple_cast(uintptr_t x) { return (uintptr_t)x; }

// Test 5: Return value with cast
uintptr_t test_return_cast(uintptr_t x) { return (uintptr_t)x; }

// Test 6: Function pointer cast
typedef void *(*step_fn)(void *, void *);
uintptr_t test_fnptr_cast(void *a, void *b) {
  step_fn f = (step_fn)a;
  return (uintptr_t)f((void *)a, (void *)b);
}

int main() {
  // Test all the functions
  int result = 0;

  result += test_cast_int(42);
  result += test_cast_typedef(10);
  result += (int)test_simple_cast(5);
  result += (int)test_return_cast(3);

  printf("All regression tests passed\n");
  return 0;
}
