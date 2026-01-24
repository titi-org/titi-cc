/* Deep nesting edge cases */

int deep_parens = ((((((((((1))))))))));
int deep_ternary = 1 ? 2 ? 3 ? 4 ? 5 : 6 : 7 : 8 : 9;
int cast_chain = (int)(long)(short)(char)42;
int mixed_ops = 1 + 2 * 3 / 4 - 5 % 6 & 7 | 8 ^ 9;
