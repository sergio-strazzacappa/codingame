#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_ISBN 500

bool check_10(char isbn[]) {
    size_t len = strlen(isbn);
    int sum = 0;
    int w = 10;
    for (size_t i = 0; i < len - 1; i++) {
        char c = isbn[i];

        if (!isdigit(c))
            return false;

        int d = c - '0';
        sum += d * w;
        w--;
    }

    int check_d = (11 - sum % 11) % 11;
    if (isdigit(isbn[len - 1]) && isbn[len - 1] - '0' != check_d)
        return false;
    if (!isdigit(isbn[len - 1]) && isbn[len - 1] == 'X' && 10 != check_d)
        return false;
    if (!isdigit(isbn[len - 1]) && isbn[len - 1] != 'X')
        return false;

    return true;
}

bool check_13(char isbn[]) {
    size_t len = strlen(isbn);
    int sum = 0;
    int w = 1;
    for (size_t i = 0; i < len - 1; i++) {
        char c = isbn[i];

        if (!isdigit(c))
            return false;

        int d = c - '0';
        sum += d * w;

        if (w == 1)
            w = 3;
        else
            w = 1;
    }

    int check_d = (10 - sum % 10) % 10;
    if (!isdigit(isbn[len - 1]))
        return false;
    if (isbn[len - 1] - '0' != check_d)
        return false;

    return true;
}

void solve(char isbns[MAX_ISBN][21], size_t n) {
    char invalids[MAX_ISBN][21];
    size_t num_invalid = 0;
    bool valid[n];

    for (size_t i = 0; i < n; i++)
        valid[i] = false;

    for (size_t i = 0; i < n; i++) {
        char *isbn = isbns[i];
        size_t len = strlen(isbn);

        if (len == 10)  valid[i] = check_10(isbn);
        if (len == 13)  valid[i] = check_13(isbn);

        if (!valid[i])
            strcpy(invalids[num_invalid++], isbn);
    }

    printf("%zu invalid:\n", num_invalid);

    for (size_t i = 0; i < n; i++) {
        if (!valid[i])
            printf("%s\n", isbns[i]);
    }
}

int main(void) {
    size_t n;
    scanf("%zu", &n);
    fgetc(stdin);

    char isbns[MAX_ISBN][21];

    for (size_t i = 0; i < n; i++) {
        fgets(isbns[i], sizeof(isbns[i]), stdin);
        isbns[i][strcspn(isbns[i], "\n")] = '\0';
    }

    solve(isbns, n);

    return EXIT_SUCCESS;
}
