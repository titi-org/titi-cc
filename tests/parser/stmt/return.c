// Test return statements
void test_return_void() {
  return;
}

int test_return_value() {
  return 42;
}

int test_return_expr(int x) {
  return x * 2 + 1;
}

int test_multiple_returns(int x) {
  if (x < 0)
    return -1;
  if (x == 0)
    return 0;
  return 1;
}

int test_return_in_loop() {
  for (int i = 0; i < 100; i++) {
    if (i == 42)
      return i;
  }
  return -1;
}
