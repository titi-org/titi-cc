// Test comma expressions
int test_comma_simple() {
  int a;
  a = (1, 2, 3);
  return a;
}

int test_comma_side_effect() {
  int a = 0, b = 0;
  int c = (a = 10, b = 20, a + b);
  return c;
}

int test_comma_in_for() {
  int sum = 0;
  for (int i = 0, j = 10; i < j; i++, j--) {
    sum += i + j;
  }
  return sum;
}
