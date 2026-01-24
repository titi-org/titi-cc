// Test do-while loops
int test_do_while_simple() {
  int i = 0;
  int sum = 0;
  do {
    sum += i;
    i++;
  } while (i < 10);
  return sum;
}

int test_do_while_once() {
  int count = 0;
  do {
    count++;
  } while (0);
  return count;
}

int test_nested_do_while() {
  int i = 0;
  int total = 0;
  do {
    int j = 0;
    do {
      total++;
      j++;
    } while (j < 2);
    i++;
  } while (i < 3);
  return total;
}
