// Test basic struct declarations
struct Point {
  int x;
  int y;
};

struct Rectangle {
  struct Point origin;
  int width;
  int height;
};

int test_struct_decl() {
  struct Point p;
  p.x = 10;
  p.y = 20;
  return p.x + p.y;
}

int test_nested_struct() {
  struct Rectangle r;
  r.origin.x = 0;
  r.origin.y = 0;
  r.width = 100;
  r.height = 50;
  return r.width * r.height;
}

struct Anonymous {
  struct { int a; int b; } inner;
};
