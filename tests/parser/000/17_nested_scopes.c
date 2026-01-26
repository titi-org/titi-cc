// Iteration 8: Nested scopes and variable shadowing
int x = 100;

int foo(int x) {
    return x + 1;
}

int main() {
    int x = 10;
    {
        int x = 20;
        x = x + 5;
    }
    return x + foo(x);
}
