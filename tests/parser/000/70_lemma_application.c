// Iteration 19: Transformation library - lemma application
int lemma_add_assoc(int a, int b, int c) {
    int x = (a + b) + c;
    int y = a + (b + c);
    return x;
}

int main() {
    return lemma_add_assoc(1, 2, 3);
}
