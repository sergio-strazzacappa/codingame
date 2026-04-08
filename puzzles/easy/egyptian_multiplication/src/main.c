#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void solve(int a, int b) {
    printf("%d * %d\n", a, b);

    int result = a * b;
    int terms[100];
    size_t terms_size = 0;

    while (b > 0) {
        if (b % 2 == 0) {
            a *= 2;
            b /= 2;
        } else {
            terms[terms_size++] = a;
            b--;
        }

        // print a step
        printf("= %d * %d", a, b);

        for (size_t i = 0; i < terms_size; i++)
            printf(" + %d", terms[i]);
        printf("\n");
    }

    // print the final result
    printf("= %d\n", result);
}

int main(void) {
    int a, b;
    scanf("%d%d", &a, &b);
    solve(MAX(a, b), MIN(a, b));

    return EXIT_SUCCESS;
}
