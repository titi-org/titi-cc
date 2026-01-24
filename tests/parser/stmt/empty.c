// Test empty and expression statements
int test_empty() {
  ;
  ;
  ;
  return 0;
}

int test_expr_stmt() {
  int a = 5;
  a;
  a + 1;
  a++;
  ++a;
  return a;
}
