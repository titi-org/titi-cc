// Test array subscript expressions
int test_subscript() {
  int arr[5];
  arr[0] = 10;
  arr[1] = 20;
  arr[2] = 30;
  return arr[0] + arr[1] + arr[2];
}

int test_pointer_subscript() {
  int arr[3];
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  int *p = arr;
  return p[0] + p[1] + p[2];
}

int test_2d_subscript() {
  int arr[2][3];
  arr[0][0] = 1;
  arr[0][1] = 2;
  arr[1][0] = 3;
  arr[1][1] = 4;
  return arr[0][0] + arr[1][1];
}
