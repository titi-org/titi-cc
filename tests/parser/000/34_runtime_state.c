// Iteration 12: Runtime evaluation - state management
int counter() {
    int count = 0;
    count = count + 1;
    return count;
}

int main() {
    int c1 = counter();
    int c2 = counter();
    return c1 + c2;
}
