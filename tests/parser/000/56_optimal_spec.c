// Iteration 16: Specialization - optimal partitioning
int loop_sum(int n, int k) {
    int sum = 0;
    int i = 0;
    while (i < n) {
        sum = sum + k;
        i = i + 1;
    }
    return sum;
}

int main() {
    return loop_sum(100, 5);
}
