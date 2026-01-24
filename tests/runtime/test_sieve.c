extern int printf(const char* fmt, ...);


int is_divisible_recursive(long long n, long long divisor) {
    if (divisor * divisor > n) return 0;
    if (n % divisor == 0) return 1;
    return is_divisible_recursive(n, divisor + 1);
}

long long find_nth_prime(long long n, long long current, long long count) {
    if (count == n) return current - 1;
    
    if (!is_divisible_recursive(current, 2)) {
         return find_nth_prime(n, current + 1, count + 1);
    }
    
    return find_nth_prime(n, current + 1, count);
}

int main() {
    long long n1 = 65536; // 2^16
    printf("%lldth prime: %lld\n", n1, find_nth_prime(n1, 2, 0));

    long long n2 = 131072; // 2^17
    printf("%lldth prime: %lld\n", n2, find_nth_prime(n2, 2, 0));

    long long n3 = 262144; // 2^18
    printf("%lldth prime: %lld\n", n3, find_nth_prime(n3, 2, 0));
    return 0;
}
