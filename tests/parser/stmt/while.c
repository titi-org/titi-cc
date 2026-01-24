// Test while loops
int test_while_simple() {
  int i = 0;
  int sum = 0;
  while (i < 10) {
    sum += i;
    i++;
  }
  return sum;
}

int test_while_empty_body() {
  int i = 0;
  while (i++ < 5)
    ;
  return i;
}

int test_nested_while() {
  int i = 0;
  int count = 0;
  while (i < 3) {
    int j = 0;
    while (j < 3) {
      count++;
      j++;
    }
    i++;
  }
  return count;
}
