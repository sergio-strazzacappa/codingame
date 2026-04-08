#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void solve(size_t n) {
    // draw the top triangle
    size_t pos = 1;
    putchar('.');
    for (size_t line = 0; line < n; line++) {
        int half = 2 * n - 1;

        for (size_t spaces = pos; spaces < half - line; spaces++)
            putchar(' ');
        for (size_t symbol = 0; symbol < (line * 2) + 1; symbol++)
            putchar('*');

        putchar('\n');
        pos = 0;
    }

    // draw the two triangles of the botom
    for (size_t line = 0; line < n; line++) {
        for (size_t spaces = 0; spaces < n - 1 - line; spaces++)
            putchar(' ');
        for (size_t symbol = 0; symbol < (line * 2) + 1; symbol++)
            putchar('*');
        for (size_t spaces = 0; spaces < (2 * n) - (line * 2) - 1; spaces++)
            putchar(' ');
        for (size_t symbol = 0; symbol < (line * 2) + 1; symbol++)
            putchar('*');

        putchar('\n');
    }
}

int main(void) {
    size_t n;
    scanf("%zu", &n);

    solve(n);

    return EXIT_SUCCESS;
}
