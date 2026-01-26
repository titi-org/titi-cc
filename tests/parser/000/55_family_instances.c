// Iteration 16: Specialization - family of instances
int transform(int base, int n) {
    int result = base;
    int i = 0;
    while (i < n) {
        result = result * 2;
        i = i + 1;
    }
    return result;
}

int main() {
    int f1 = transform(1, 3);
    int f2 = transform(2, 3);
    int f3 = transform(3, 3);
    return f1 + f2 + f3;
}
