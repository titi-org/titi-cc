// Iteration 16: Generalization - multiple parameters
int combine(int a, int b, int c) {
    int x = a + b;
    int y = x + c;
    return y;
}

int main() {
    int r1 = combine(1, 2, 3);
    int r2 = combine(4, 5, 6);
    return r1 + r2;
}
