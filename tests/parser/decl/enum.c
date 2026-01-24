// Test enum declarations
enum Color { RED, GREEN, BLUE };

enum Status {
  OK = 0,
  ERROR = -1,
  PENDING = 1
};

int test_enum() {
  enum Color c = RED;
  enum Status s = OK;
  return c + s;
}

int test_enum_values() {
  return RED + GREEN + BLUE + OK + ERROR + PENDING;
}
