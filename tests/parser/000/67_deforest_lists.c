// Iteration 19: Transformation library - deforestation
int sum_twice(int n) {
    int sum1 = 0;
    int sum2 = 0;
    int i = 0;
    while (i < n) {
        sum1 = sum1 + i;
        sum2 = sum2 + i;
        i = i + 1;
    }
    return sum1 + sum2;
}

int main() {
    return sum_twice(10);
}
