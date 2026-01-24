/* Nested type definitions edge cases */

struct A {
    struct B {
        struct C {
            int x;
        } c;
    } b;
} a;

struct Empty {};

enum E { A, B, C, };
