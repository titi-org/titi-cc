// Test switch statements
int test_switch_simple(int x) {
  switch (x) {
    case 1:
      return 10;
    case 2:
      return 20;
    default:
      return 0;
  }
}

int test_switch_fallthrough(int x) {
  int result = 0;
  switch (x) {
    case 1:
    case 2:
    case 3:
      result = 100;
      break;
    case 4:
      result = 200;
      break;
    default:
      result = -1;
  }
  return result;
}

int test_switch_nested(int x, int y) {
  switch (x) {
    case 1:
      switch (y) {
        case 1: return 11;
        case 2: return 12;
      }
      break;
    case 2:
      return 20;
  }
  return 0;
}
