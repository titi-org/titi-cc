// Test bitfield declarations
struct Flags {
  unsigned int a : 1;
  unsigned int b : 2;
  unsigned int c : 5;
  unsigned int : 0;
  unsigned int d : 8;
};

int test_bitfield() {
  struct Flags f;
  f.a = 1;
  f.b = 3;
  f.c = 16;
  f.d = 255;
  return f.a + f.b + f.c + f.d;
}
