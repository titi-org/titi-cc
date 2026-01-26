// Iteration 15: Supercompilation whistle - simple unfold
int twice(int x) {
    return x + x;
}

int double_twice(int x) {
    return twice(twice(x));
}

int main() {
    return double_twice(5);
}
