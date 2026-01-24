// Test C23 alignas specifier

// alignas with constant expression
alignas(16) int aligned_global;

// alignas with type
alignas(double) int aligned_to_double;

// alignas in local variable
int test_alignas_local() {
  alignas(8) int aligned_local = 42;
  return aligned_local;
}

// struct (alignas in struct members needs separate grammar fix)
struct AlignedStruct {
  int x;
  double y;
};

// multiple alignas specifiers
alignas(64) static int heavily_aligned;

int test_alignas_struct() {
  struct AlignedStruct s;
  s.x = 10;
  s.y = 20.0;
  return s.x;
}
