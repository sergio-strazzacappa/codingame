#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HORSES 100000

void debug(int ps[], size_t n) {
    fprintf(stderr, "[DEBUG] [");
    for (size_t i = 0; i < n; i++) {
        fprintf(stderr, "%d", ps[i]);
        if (i != n - 1)
            fprintf(stderr, ", ");
    }
    fprintf(stderr, "]\n");
}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void solve(int ps[], size_t n) {
    qsort(ps, n, sizeof(int), cmp);

    int min = INT_MAX;

    for (size_t i = 0; i < n - 1; i++) {
        int diff = ps[i + 1] - ps[i];

        if (diff < min)
            min = diff;
    }

    printf("%d\n", min);
}


int main(void) {
    size_t n;
    int ps[MAX_HORSES];
    scanf("%zu", &n);

    for (size_t i = 0; i < n; i++)
        scanf("%d", &ps[i]);

    debug(ps, n);
    solve(ps, n);

    return EXIT_SUCCESS;
}
