// Test array declarations
int test_arrays() {
  int arr1[10];
  int arr2[5] = {1, 2, 3, 4, 5};
  int arr3[] = {10, 20, 30};

  arr1[0] = 1;
  arr1[9] = 10;

  return arr1[0] + arr2[0] + arr3[0];
}

int test_2d_array() {
  int mat[3][4];
  mat[0][0] = 1;
  mat[2][3] = 12;
  return mat[0][0] + mat[2][3];
}

int test_array_of_pointers() {
  int a = 1, b = 2, c = 3;
  int *arr[3] = {&a, &b, &c};
  return *arr[0] + *arr[1] + *arr[2];
}
