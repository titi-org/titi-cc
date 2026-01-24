// Test if/else statements
int test_if_simple(int x) {
  if (x > 0)
    return 1;
  return 0;
}

int test_if_else(int x) {
  if (x > 0)
    return 1;
  else
    return -1;
}

int test_if_block(int x) {
  if (x > 0) {
    int y = x * 2;
    return y;
  }
  return 0;
}

int test_if_else_if(int x) {
  if (x > 0)
    return 1;
  else if (x < 0)
    return -1;
  else
    return 0;
}

int test_nested_if(int x, int y) {
  if (x > 0) {
    if (y > 0)
      return 1;
    else
      return 2;
  }
  return 0;
}
