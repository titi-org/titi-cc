// Test string literals
extern int printf(const char *fmt, ...);

int test_string_literals() {
  const char *a = "hello";
  const char *b = "world";
  const char *c = "line1\nline2";
  const char *d = "tab\there";
  const char *e = "";
  printf("%s %s\n", a, b);
  printf("%s\n", c);
  printf("%s\n", d);
  return 0;
}
