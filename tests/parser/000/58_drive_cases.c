// Iteration 17: Driving - case splitting
int classify(int x) {
    if (x < 0) {
        return 0 - x;
    }
    if (x == 0) {
        return 0;
    }
    return x;
}

int main() {
    return classify(42) + classify(-42) + classify(0);
}
