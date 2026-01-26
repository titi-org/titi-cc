// Iteration 17: Driving - fold optimization
int step(int x, int n) {
    int result = x;
    int i = 0;
    while (i < n) {
        result = result + 1;
        i = i + 1;
    }
    return result;
}

int main() {
    return step(0, 10);
}
