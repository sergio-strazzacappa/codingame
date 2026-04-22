#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

size_t next(size_t x) {
    size_t result = x;

    while (x > 0) {
        result += x % 10;
        x /= 10;
    }

    return result;
}

void solve(size_t r1, size_t r2) {
    while (r1 != r2) {
        if (r1 < r2)    r1 = next(r1);
        else            r2 = next(r2);
    }

    printf("%zu\n", r1);
}

int main(void) {
    size_t r1, r2;
    scanf("%zu%zu", &r1, &r2);

    solve(r1, r2);

    return EXIT_SUCCESS;
}
