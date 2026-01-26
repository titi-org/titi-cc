// Iteration 15: Supercompilation whistle - linear recursion
int sum_list(int n) {
    if (n == 0) {
        return 0;
    }
    return n + sum_list(n - 1);
}

int main() {
    return sum_list(10);
}
