// Test cast expressions
int test_basic_cast() {
  double d = 3.14;
  int i = (int)d;
  return i;
}

long test_pointer_cast() {
  int a = 42;
  long ptr = (long)&a;
  int *p = (int *)ptr;
  return *p;
}

int test_nested_cast() {
  char c = 'A';
  int i = (int)(unsigned char)c;
  return i;
}
