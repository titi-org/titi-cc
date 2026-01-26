// Iteration 10: Struct basic declaration and member access
struct point {
    int x;
    int y;
};

int main() {
    struct point p;
    p.x = 10;
    p.y = 20;
    return p.x + p.y;
}
