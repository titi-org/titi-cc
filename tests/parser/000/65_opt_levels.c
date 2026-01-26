// Iteration 18: End-to-end compilation - opt levels
int opt_test(int n) {
    int x = 1 + 1;
    int y = x * 2;
    int z = y + 0;
    int i = 0;
    while (i < n) {
        z = z + 1;
        i = i + 1;
    }
    return z;
}

int main() {
    return opt_test(100);
}
