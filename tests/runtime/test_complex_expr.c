// #include <stdio.h>
extern int printf(const char *format, ...);

// Test complex expressions
long ternary_max(long a, long b) { return a > b ? a : b; }

long nested_ternary(long a, long b, long c) {
  return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

long complex_arithmetic(long x, long y, long z) {
  return (x + y) * (z - x) / (y + 1);
}

long logical_expr(long a, long b, long c) {
  return (a > 0 && b > 0) || (c < 0) ? 1 : 0;
}

int main() {
  printf("max(5, 3): %ld\n", (long)ternary_max(5, 3));
  printf("max(7, 9, 2): %ld\n", (long)nested_ternary(7, 9, 2));
  printf("complex(10, 5, 20): %ld\n", (long)complex_arithmetic(10, 5, 20));
  printf("logical(1, 1, 0): %ld\n", (long)logical_expr(1, 1, 0));
  printf("logical(0, 1, -1): %ld\n", (long)logical_expr(0, 1, -1));
  return 0;
}
