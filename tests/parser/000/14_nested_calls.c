int foo(int x) {
    return x * 2;
}

int main() {
    int a = 5;
    int b = foo(a);
    int c = foo(foo(a));
    return c;
}
