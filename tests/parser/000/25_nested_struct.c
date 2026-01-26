// Iteration 10: Nested struct definition
struct inner {
    int value;
};

struct outer {
    int id;
    struct inner in;
};

int main() {
    struct outer o;
    o.id = 1;
    o.in.value = 42;
    return 0;
}
