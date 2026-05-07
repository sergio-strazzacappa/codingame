#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <limits.h>

unsigned long vault_time(const size_t C, const size_t N) {
    return pow(10, N) * pow(5, C - N);
}

size_t array_min(const unsigned long a[], const size_t n) {
    unsigned long min = ULONG_MAX;
    size_t index = 0;

    for (size_t i = 0; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
            index = i;
        }

        if (min == 0)
            break;
    }

    return index;
}

size_t array_max(const unsigned long a[], const size_t n) {
    unsigned long max = a[0];
    size_t index = 0;

    for (size_t i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
            index = i;
        }
    }

    return index;
}

int main(void) {
    size_t R, V;
    scanf("%zu%zu", &R, &V);

    unsigned long times[5] = {0};
    for (size_t i = 0; i < V; i++) {
        size_t C, N;
        scanf("%zu%zu", &C, &N);

        size_t index = array_min(times, R);

        times[index] += vault_time(C, N);
    }

    size_t index = array_max(times, R);
    printf("%lu\n", times[index]);

    return EXIT_SUCCESS;
}
