#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

typedef struct complex_s {
    double real;
    double im;
} complex_t;

/**
 * c: complex number a + bi
 * m: number of iterations
 */
void solve(const char c[], size_t m) {
    complex_t n = {0};
    char *s;

    if ((s = strrchr(c, '+')) || (s = strrchr(c, '-'))) {
        char t = *s;
        *s = '\0';
        n.real = atof(c);
        *s = t;
        n.im = atof(s);
    }

    complex_t prev = {0};
    for (size_t i = 1; i <= m; i++) {
        complex_t tmp = prev;
        prev.real = (tmp.real * tmp.real - tmp.im * tmp.im) + n.real;
        prev.im = 2 * tmp.real * tmp.im + n.im;
        double abs = sqrt(pow(prev.real, 2) + pow(prev.im, 2));

        if (abs >= 2) {
            printf("%zu\n", i);
            return;
        }
    }

    printf("%zu\n", m);
}

int main(void) {
    char c[64];
    fgets(c, sizeof(c), stdin);
    c[strcspn(c, "\n")] = '\0';

    size_t m;
    scanf("%zu", &m);

    solve(c, m);

    return EXIT_SUCCESS;
}
