/* Complex declarator edge cases */

int (*(*f)(int))[10];
int *(*p)[10];
int (*g(int))(int);

typedef int INT;
typedef INT MYINT;
MYINT x;

typedef struct { int x; int y; } Point;
Point origin;
