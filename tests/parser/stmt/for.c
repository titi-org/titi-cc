// Test for loops
int test_for_simple() {
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += i;
  }
  return sum;
}

int test_for_empty_init() {
  int i = 0;
  int sum = 0;
  for (; i < 5; i++) {
    sum += i;
  }
  return sum;
}

int test_for_empty_cond() {
  int sum = 0;
  for (int i = 0; ; i++) {
    if (i >= 5) break;
    sum += i;
  }
  return sum;
}

int test_for_empty_incr() {
  int sum = 0;
  for (int i = 0; i < 5; ) {
    sum += i;
    i++;
  }
  return sum;
}

int test_for_all_empty() {
  int i = 0;
  int sum = 0;
  for (;;) {
    if (i >= 5) break;
    sum += i;
    i++;
  }
  return sum;
}

int test_for_empty_body() {
  int i;
  for (i = 0; i < 5; i++)
    ;
  return i;
}

int test_nested_for() {
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      count++;
    }
  }
  return count;
}

int test_for_with_continue() {
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) continue;
    sum += i;
  }
  return sum;
}

int test_for_decl_outside() {
  int sum = 0;
  int i;
  for (i = 0; i < 5; i++) {
    sum += i;
  }
  return sum + i;
}
