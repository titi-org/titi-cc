// Test ternary operator
int test_ternary_simple() {
  int a = 5, b = 3;
  return a > b ? a : b;
}

int test_ternary_nested() {
  int a = 1, b = 2, c = 3;
  return a > b ? a : (b > c ? b : c);
}

int test_ternary_chain() {
  int x = 2;
  return x == 1 ? 10 : x == 2 ? 20 : 30;
}
