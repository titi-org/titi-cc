// Test break and continue
int test_break_while() {
  int i = 0;
  while (1) {
    if (i >= 5)
      break;
    i++;
  }
  return i;
}

int test_continue_while() {
  int sum = 0;
  int i = 0;
  while (i < 10) {
    i++;
    if (i % 2 == 0)
      continue;
    sum += i;
  }
  return sum;
}

int test_break_for() {
  int last = 0;
  for (int i = 0; i < 100; i++) {
    if (i > 5)
      break;
    last = i;
  }
  return last;
}

int test_continue_for() {
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 1)
      continue;
    sum += i;
  }
  return sum;
}

int test_nested_break() {
  int count = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (j == 2)
        break;
      count++;
    }
  }
  return count;
}
