#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

void solve(const char text[20][101], const size_t n) {
    for (size_t i = 0; i < n; i++) {
        size_t len = strlen(text[i]);

        for (size_t j = 0; j < len; j++) {
            // iterate until found a C, then check if the bounds of the
            // hydrocarbon found are valid
            if (text[i][j] == 'C') {
                int bounds = 4 - (text[i][j + 2] - '0');

                // check the bounds in every direction

                // UP
                if (i > 0 && isdigit(text[i - 1][j + 1]))
                    bounds -= text[i - 1][j + 1] - '0';

                // RIGHT
                if (j < len - 4 && isdigit(text[i][j + 4]))
                    bounds -= text[i][j + 4] - '0';

                // DOWN
                if (i < n - 1 && isdigit(text[i + 1][j + 1]))
                    bounds -= text[i + 1][j + 1] - '0';

                // LEFT
                if (j > 2 && isdigit(text[i][j - 2]))
                    bounds -= text[i][j - 2] - '0';

                if (bounds != 0) {
                    printf("INVALID\n");
                    return;
                }
            }
        }
    }

    printf("VALID\n");
}

int main(void) {
    size_t n;
    scanf("%zu", &n);
    fgetc(stdin);

    char text[20][101];

    for (size_t i = 0; i < n; i++) {
        fgets(text[i], sizeof(text[i]), stdin);
        text[i][strcspn(text[i], "\n")] = '\0';
    }

    solve(text, n);

    return EXIT_SUCCESS;
}
