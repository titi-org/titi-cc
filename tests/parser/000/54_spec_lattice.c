// Iteration 16: Specialization - lattice structure
int generic(int x) {
    if (x == 0) {
        return 0;
    }
    return x * generic(x - 1);
}

int main() {
    return generic(5);
}
