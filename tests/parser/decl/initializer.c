// Test various initializer forms
int test_scalar_init() {
  int a = 42;
  int b = (10 + 5);
  int c = a * 2;
  return a + b + c;
}

int test_array_init() {
  int arr1[5] = {1, 2, 3, 4, 5};
  int arr2[] = {10, 20};
  int arr3[10] = {1};
  return arr1[0] + arr2[0] + arr3[0];
}

struct Point { int x; int y; };

int test_struct_init() {
  struct Point p1 = {10, 20};
  struct Point p2 = {30, 40};
  return p1.x + p2.y;
}

int test_nested_init() {
  int mat[2][3] = {{1, 2, 3}, {4, 5, 6}};
  return mat[0][0] + mat[1][2];
}
