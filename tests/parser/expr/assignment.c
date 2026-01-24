// Test assignment operators
int test_assignment() {
  int a = 10;
  a += 5;
  a -= 3;
  a *= 2;
  a /= 4;
  a %= 3;
  return a;
}

int test_bitwise_assignment() {
  int a = 0xFF;
  a &= 0x0F;
  a |= 0xF0;
  a ^= 0x55;
  a <<= 2;
  a >>= 1;
  return a;
}

int test_chain_assignment() {
  int a, b, c;
  a = b = c = 42;
  return a + b + c;
}
