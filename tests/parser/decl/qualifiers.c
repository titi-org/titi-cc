// Test type qualifiers
const int CONST_VAL = 100;

int test_const() {
  const int a = 42;
  const int *p1 = &a;
  int * const p2 = (int*)&a;
  const int * const p3 = &a;
  return *p1;
}

int test_volatile() {
  volatile int v = 0;
  v = 10;
  return v;
}

int test_restrict() {
  int arr[10];
  int * restrict p = arr;
  *p = 42;
  return *p;
}
