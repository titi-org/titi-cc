// Test function call expressions
extern int printf(const char *fmt, ...);

int no_args() {
  return 42;
}

int one_arg(int x) {
  return x * 2;
}

int three_args(int a, int b, int c) {
  return a + b + c;
}

int test_calls() {
  int r1 = no_args();
  int r2 = one_arg(5);
  int r3 = three_args(1, 2, 3);
  int r4 = one_arg(no_args());
  return r1 + r2 + r3 + r4;
}
