/* Advanced initializer edge cases */

int arr[10] = { [5] = 5, [3] = 3 };
int *compound = (int[]){1, 2, 3};
struct { int a; int b; } s = { .a = 1, .b = 2 };
