// Iteration 19: Transformation library - loop fusion
int fused_loops(int n) {
    int result = 0;
    int i = 0;
    while (i < n) {
        result = result + i;
        result = result * 1;
        i = i + 1;
    }
    return result;
}

int main() {
    return fused_loops(20);
}
