// Test function declarations
int simple_func(int a, int b);
void no_return(void);
int varargs_func(const char *fmt, ...);

int simple_func(int a, int b) {
  return a + b;
}

void no_return(void) {
  return;
}

static inline int inline_func(int x) {
  return x * 2;
}

int test_func_decls() {
  return simple_func(1, 2) + inline_func(3);
}
