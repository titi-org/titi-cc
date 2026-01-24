#include <stdio.h>

// Test various loop constructs
long sum_while(long n) {
  long sum = 0;
  long i = 1;
  while (i <= n) {
    sum = sum + i;
    i = i + 1;
  }
  return sum;
}

long sum_do_while(long n) {
  long sum = 0;
  long i = 1;
  do {
    sum = sum + i;
    i = i + 1;
  } while (i <= n);
  return sum;
}

long sum_for(long n) {
  long sum = 0;
  for (long i = 1; i <= n; i = i + 1) {
    sum = sum + i;
  }
  return sum;
}

int main() {
  printf("while: %ld\n", (long)sum_while(10));
  printf("do-while: %ld\n", (long)sum_do_while(10));
  printf("for: %ld\n", (long)sum_for(10));
  return 0;
}
