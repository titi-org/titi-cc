// Iteration 17: Driving - fold detection
int twice(int x) {
    return x + x;
}

int quad(int x) {
    return twice(twice(x));
}

int main() {
    return quad(10);
}
