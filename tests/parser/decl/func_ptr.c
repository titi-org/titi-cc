// Test function pointer declarations
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int test_func_ptr() {
  int (*fp)(int, int);
  fp = add;
  int r1 = fp(10, 5);
  fp = sub;
  int r2 = fp(10, 5);
  return r1 + r2;
}

int apply(int (*op)(int, int), int x, int y) {
  return op(x, y);
}

int test_func_ptr_param() {
  return apply(add, 3, 4) + apply(sub, 7, 2);
}
