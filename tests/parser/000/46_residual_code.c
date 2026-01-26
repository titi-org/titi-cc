// Iteration 14: Partial evaluation - residual program
int multiply(int a, int b) {
    int result = 0;
    int i = 0;
    while (i < b) {
        result = result + a;
        i = i + 1;
    }
    return result;
}

int main() {
    return multiply(7, 6);
}
