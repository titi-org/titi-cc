#include <stdio.h>

static inline int add(int a, int b) { return a + b; }

static __inline__ int sub(int a, int b) { return a - b; }

// Simple function to test for loop
int sum_to_n(int n) {
  int sum = 0;
  int i;
  for (i = 1; i <= n; i++) {
    sum = sum + i;
  }
  return sum;
}

int main() {
  printf("Add: %ld\n", (long)add(10, 20));
  printf("Sub: %ld\n", (long)sub(20, 10));
  printf("Sum 1-10: %ld\n", (long)sum_to_n(10));
  return 0;
}
