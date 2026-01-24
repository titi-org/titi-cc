// Test storage class specifiers
static int static_var = 10;
extern int extern_var;

static int static_func() {
  return static_var;
}

int test_auto() {
  auto int a = 1;
  register int b = 2;
  return a + b;
}

int test_static_local() {
  static int counter = 0;
  counter++;
  return counter;
}
