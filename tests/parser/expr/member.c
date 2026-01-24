// Test member access expressions
struct Point {
  int x;
  int y;
};

int test_dot_access() {
  struct Point p;
  p.x = 10;
  p.y = 20;
  return p.x + p.y;
}

int test_arrow_access() {
  struct Point p;
  struct Point *ptr = &p;
  ptr->x = 30;
  ptr->y = 40;
  return ptr->x + ptr->y;
}

struct Nested {
  struct Point p;
  int z;
};

int test_nested_member() {
  struct Nested n;
  n.p.x = 1;
  n.p.y = 2;
  n.z = 3;
  return n.p.x + n.p.y + n.z;
}
