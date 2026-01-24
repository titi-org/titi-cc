/* All assignment operators edge cases */

void f(void) {
    int a, b, c, d, e, f, g;
    a = b += c -= d *= e /= f %= g;
    a &= b |= c ^= d <<= e >>= f;
}
