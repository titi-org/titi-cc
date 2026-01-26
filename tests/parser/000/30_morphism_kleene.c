// Iteration 11: Morphism mapping - loop as fixpoint
int sum_to_n(int n) {
    int sum = 0;
    int i = 0;
    while (i < n) {
        sum = sum + i;
        i = i + 1;
    }
    return sum;
}

int main() {
    return sum_to_n(10);
}
