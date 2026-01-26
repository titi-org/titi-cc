// Iteration 10: Pointer to struct with arrow operator
struct point {
    int x;
    int y;
};

int main() {
    struct point p;
    struct point *ptr;
    ptr = *(&p);
    return 0;
}
