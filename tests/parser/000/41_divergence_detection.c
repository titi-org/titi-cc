// Iteration 13: Program representation - divergence detection
int is_even(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }
    return is_odd(n - 1);
}

int is_odd(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return is_even(n - 1);
}

int main() {
    return is_even(4);
}
