/* sizeof and alignof edge cases */

struct S { int a; double b; };
int x = sizeof(int) + sizeof x + sizeof(struct S);
int y = alignof(double);
