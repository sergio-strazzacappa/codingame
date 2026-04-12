#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

// reverse the digits in the string
void reverse(char *str) {
    size_t len = strlen(str);

    for (size_t i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

// swap the Ts and 1s in the resulting ternary number.
// swapping every T for every 1 in the positive or abs-value of n makes the
// negative version of n
void swap(char *str) {
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (str[i] == 'T') {
            str[i] = '1';
            continue;
        }

        if (str[i] == '1') {
            str[i] = 'T';
            continue;
        }
    }
}

void solve(int n, char b[]) {
    size_t i = 0;
    bool neg = false;

    if (n < 0) {
        n = -n;
        neg = true;
    }

    if (n == 0)
        b[i++] = '0';

    while (n != 0) {
        int remainder = n % 3;

        switch (remainder) {
            case 0:
                b[i++] = '0';
                break;
            case 1:
                b[i++] = '1';
                break;
            case 2:
                b[i++] = 'T';
                n++;
                break;
            default:
                assert(0);
                break;
        }
        n /= 3;
    }
    b[i] = '\0';

    reverse(b);
    if (neg)
        swap(b);
}

int main(void) {
    int n;
    scanf("%d", &n);

    char b[512];
    solve(n, b);

    printf("%s\n", b);

    return EXIT_SUCCESS;
}
