extern int printf(const char* fmt, ...);

int factorial(int n)
{
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main(void) {
    int f = factorial(13);
    printf("%i\n", f);
    return 0;
}
