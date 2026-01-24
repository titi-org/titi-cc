// Test operator precedence
int test_arith_precedence() {
  // * and / before + and -
  return 2 + 3 * 4 - 6 / 2;
}

int test_compare_precedence() {
  // comparison before logical
  return 1 < 2 && 3 > 2;
}

int test_bitwise_precedence() {
  // & before | before ^
  return 0xFF & 0x0F | 0xF0 ^ 0x55;
}

int test_mixed_precedence() {
  int a = 2, b = 3, c = 4;
  // unary before binary, * before +, comparison before &&
  return -a + b * c > 5 && !0;
}

int test_parentheses() {
  // parentheses override precedence
  return (2 + 3) * (4 - 1);
}
