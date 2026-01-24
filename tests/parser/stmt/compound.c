// Test compound statements
int test_compound() {
  {
    int a = 1;
    int b = 2;
    a + b;
  }
  return 0;
}

int test_nested_compound() {
  {
    int x = 1;
    {
      int y = 2;
      {
        int z = 3;
        x + y + z;
      }
    }
  }
  return 0;
}

int test_empty_compound() {
  {}
  return 0;
}
