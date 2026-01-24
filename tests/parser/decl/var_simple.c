// Test simple variable declarations
int global_int;
int global_init = 42;

int test_local_vars() {
  int a;
  int b = 10;
  int c, d, e;
  int f = 1, g = 2, h = 3;
  return a + b + c + d + e + f + g + h;
}
