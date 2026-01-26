// Iteration 15: Supercompilation whistle - recursive unfold
int countdown(int n) {
    if (n == 0) {
        return 0;
    }
    return countdown(n - 1);
}

int main() {
    return countdown(100);
}
