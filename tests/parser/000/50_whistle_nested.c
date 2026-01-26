// Iteration 15: Supercompilation whistle - nested recursion
int nested(int n) {
    if (n == 0) {
        return 1;
    }
    return n * nested(n - 1);
}

int main() {
    return nested(5);
}
