// Test unary operators
int test_unary() {
  int a = 5;
  int neg = -a;
  int pos = +a;
  int not_op = !a;
  int bitnot = ~a;
  return neg + pos + not_op + bitnot;
}

int test_increment() {
  int a = 5;
  int pre_inc = ++a;
  int pre_dec = --a;
  int post_inc = a++;
  int post_dec = a--;
  return pre_inc + pre_dec + post_inc + post_dec;
}

int test_address_deref() {
  int a = 42;
  int *p = &a;
  int val = *p;
  return val;
}

int test_sizeof_expr() {
  int a = 0;
  int s1 = sizeof(a);
  int s2 = sizeof(int);
  int s3 = sizeof(int *);
  return s1 + s2 + s3;
}
