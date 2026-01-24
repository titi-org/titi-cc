// Test goto and labels
int test_goto_forward() {
  int x = 0;
  goto end;
  x = 100;
end:
  return x;
}

int test_goto_backward() {
  int i = 0;
loop:
  if (i < 5) {
    i++;
    goto loop;
  }
  return i;
}

int test_multiple_labels() {
  int x = 0;
first:
  x = 1;
second:
  x = 2;
third:
  x = 3;
  return x;
}
