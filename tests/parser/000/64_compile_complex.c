// Iteration 18: End-to-end compilation - complex
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a - (a / b) * b;
        a = temp;
    }
    return a;
}

int main() {
    return gcd(48, 18);
}
