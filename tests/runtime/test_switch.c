#include <stdio.h>

// Test switch statement
const char *get_day_name(int day) {
  switch (day) {
  case 1:
    return "Monday";
  case 2:
    return "Tuesday";
  case 3:
    return "Wednesday";
  case 4:
    return "Thursday";
  case 5:
    return "Friday";
  case 6:
    return "Saturday";
  case 7:
    return "Sunday";
  default:
    return "Invalid";
  }
}

int classify_number(int n) {
  switch (n) {
  case 0:
    return 0;
  case 1:
  case 2:
  case 3:
    return 1;
  default:
    return 2;
  }
}

int main() {
  printf("Day 1: %s\n", get_day_name(1));
  printf("Day 7: %s\n", get_day_name(7));
  printf("Day 99: %s\n", get_day_name(99));
  printf("Classify 0: %d\n", classify_number(0));
  printf("Classify 2: %d\n", classify_number(2));
  printf("Classify 5: %d\n", classify_number(5));
  return 0;
}
