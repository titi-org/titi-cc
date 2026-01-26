// Iteration 15: Supercompilation whistle - tree depth control
int append(int a, int b) {
    return a + b;
}

int main() {
    int x = append(1, 2);
    int y = append(x, 3);
    int z = append(y, 4);
    return z;
}
