// Iteration 11: Morphism mapping - conditional as branching
int abs_value(int x) {
    if (x < 0) {
        return 0 - x;
    }
    return x;
}

int main() {
    return abs_value(-42);
}
