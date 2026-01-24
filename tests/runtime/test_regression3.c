/* Regression against categorical emitter emitting extra identity/nat wrappers */

int apply(int a, int b) {
    return (a + 1) * (b - 2);
}

int main(void) {
    int result = apply(3, 5);
    return result == 12 ? 0 : 1;
}
