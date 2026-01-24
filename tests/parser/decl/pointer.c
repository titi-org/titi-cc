// Test pointer declarations
int test_pointers() {
  int a = 42;
  int *p1 = &a;
  int **p2 = &p1;
  int ***p3 = &p2;

  const int *cp = &a;
  int * const pc = &a;
  const int * const cpc = &a;

  return ***p3;
}
