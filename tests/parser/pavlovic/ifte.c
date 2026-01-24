/* ifte keyword edge case */

void test_ifte(void) {
    ifte(1, 2, 3);
    ifte(a > b, a, b);
}
