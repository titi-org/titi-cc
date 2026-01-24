#include <stdio.h>

// Test struct and union definitions
struct Point {
  long x;
  long y;
};

union Data {
  long i;
  double d;
};

struct Point make_point(long x, long y) {
  struct Point p;
  p.x = x;
  p.y = y;
  return p;
}

long point_distance_squared(struct Point p) { return p.x * p.x + p.y * p.y; }

int main() {
  struct Point p1 = make_point(3, 4);
  printf("Point: (%ld, %ld)\n", (long)p1.x, (long)p1.y);
  printf("Distance squared: %ld\n", (long)point_distance_squared(p1));

  union Data d;
  d.i = 42;
  printf("Union int: %ld\n", (long)d.i);

  return 0;
}
