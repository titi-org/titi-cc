#include <stdio.h>

long simple_const() { return 123; }

long add_vars(long x, long y) { return x + y; }

long factorial_recursive(long n) {
  if (n <= 1)
    return 1;
  return n * factorial_recursive(n - 1);
}

long multiple_args(long a, long b, long c, long d) { return (a + b) * (c - d); }

int main() {
  printf("simple_const: %ld\n", simple_const());
  printf("add_vars(10, 20): %ld\n", add_vars(10, 20));
  printf("factorial_recursive(5): %ld\n", factorial_recursive(5));
  printf("multiple_args(1, 2, 10, 5): %ld\n", multiple_args(1, 2, 10, 5));
  return 0;
}
