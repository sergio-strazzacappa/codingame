#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

int sum_of_digits(int x) {
    int sum = 0;

    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }

    return sum;
}

void solve(int r1) {
    char str[16];

    if (snprintf(str, sizeof(str), "%d", r1) < 0) {
        fprintf(stderr, "[ERROR] Can't get the len of r1\n");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(str);
    size_t max = len * 9;

    for (size_t i = 1; i <= max; i++) {
        int prev = r1 - i;

        if ((prev + sum_of_digits(prev)) == r1) {
            printf("YES\n");
            return;
        }
    }

    printf("NO\n");
}

int main(void) {
    int r1;
    scanf("%d", &r1);

    solve(r1);

    return EXIT_SUCCESS;
}
