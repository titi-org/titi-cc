// Test binary operators
int test_arithmetic() {
  int a = 10, b = 3;
  int add = a + b;
  int sub = a - b;
  int mul = a * b;
  int div = a / b;
  int mod = a % b;
  return add + sub + mul + div + mod;
}

int test_comparison() {
  int a = 5, b = 3;
  int lt = a < b;
  int gt = a > b;
  int le = a <= b;
  int ge = a >= b;
  int eq = a == b;
  int ne = a != b;
  return lt + gt + le + ge + eq + ne;
}

int test_bitwise() {
  int a = 0xF0, b = 0x0F;
  int and_op = a & b;
  int or_op = a | b;
  int xor_op = a ^ b;
  int shl = a << 4;
  int shr = a >> 4;
  return and_op + or_op + xor_op + shl + shr;
}

int test_logical() {
  int a = 1, b = 0;
  int and_op = a && b;
  int or_op = a || b;
  return and_op + or_op;
}
