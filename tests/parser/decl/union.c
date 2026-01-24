// Test union declarations
union IntOrFloat {
  int i;
  float f;
};

int test_union() {
  union IntOrFloat u;
  u.i = 42;
  int a = u.i;
  u.f = 3.14f;
  return a;
}

union Tagged {
  struct { char tag; int value; } as_int;
  struct { char tag; float value; } as_float;
};
