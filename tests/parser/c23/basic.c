// Test C23 basic features

// Boolean type and literals
bool test_bool_literal() {
  bool a = true;
  bool b = false;
  return a && !b;
}

// nullptr literal
int *test_nullptr() {
  int *p = nullptr;
  return p;
}

// static_assert with message
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

// static_assert without message (C23)
static_assert(sizeof(char) == 1);

// thread_local storage class
thread_local int tls_var = 42;

int test_thread_local() {
  return tls_var;
}

// constexpr (C23)
constexpr int CONSTANT = 100;

int test_constexpr() {
  constexpr int local_const = 50;
  return CONSTANT + local_const;
}

// alignof (alignas tested separately after parser fix)
int test_alignof() {
  int alignment = alignof(double);
  return alignment;
}
