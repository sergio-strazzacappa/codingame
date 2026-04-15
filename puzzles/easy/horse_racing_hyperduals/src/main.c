#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

#define MAX_HORSES 600

typedef struct vector_s {
    int velocity;
    int elegance;
} vector_t;

void debug(vector_t horses[], size_t n) {
    fprintf(stderr, "Number of horses:%zu\n", n);
    fprintf(stderr, "[\n");

    for (size_t i = 0; i < n; i++)
        fprintf(stderr, "\t(%d, %d)\n", horses[i].velocity, horses[i].elegance);
    fprintf(stderr, "]\n");
}

unsigned int distance(vector_t v1, vector_t v2) {
    return (abs((int)v1.velocity - v2.velocity) + abs(v1.elegance - v2.elegance));
}

void solve(vector_t horses[], size_t n) {
    unsigned int min = UINT_MAX;

    for (size_t i = 0; i < n - 1 && min > 0; i++) {
        for (size_t j = i + 1; j < n && min > 0; j++) {
            unsigned int d = distance(horses[i], horses[j]);

            if (d < min)
                min = d;
        }
    }

    printf("%u\n", min);
}

int main(void) {
    size_t n;
    vector_t horses[MAX_HORSES];
    scanf("%zu", &n);

    for (size_t i = 0; i < n; i++) {
        int velocity, elegance;
        scanf("%d%d", &velocity, &elegance);

        horses[i] = (vector_t){velocity, elegance};
    }

    debug(horses, n);
    solve(horses, n);

    return EXIT_SUCCESS;
}
