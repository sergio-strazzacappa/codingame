#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*
 * Strategy
 * --------
 *  Copy the pattern n times to cover the length of the current line
 *  Iterate over the extended pattern, cheking the number of incorrect chars
 *
 *  1. If there are exactly 0 incorrect chars the row is alligned and correct
 *  2. If there are more than 1 incorrect chars the row is not alligned so move
 *  the extended pattern and try again
 *  3. If there is exactle 1 incorrect char then that is the wrong tile
 */

int main(void) {
    size_t size;
    scanf("%zu", &size);
    fgetc(stdin);

    char pattern[129];
    scanf("%128[^\n]", pattern);
    fgetc(stdin);

    size_t pattern_len = strlen(pattern);

    for (size_t y = 0; y < size; y++) {
        char row[129];
        scanf("%128[^\n]", row);
        fgetc(stdin);

        size_t row_len = strlen(row);
        size_t times = (int)ceil((double)row_len / (double)pattern_len);

        char extended_pattern[256];
        strcpy(extended_pattern, pattern);

        for (size_t i = 1; i < times; i++)
            strcat(extended_pattern, pattern);

        size_t len = strlen(extended_pattern);

        for (size_t i = 0; i < len; i++) {
            size_t correct = 0;
            size_t incorrect = 0;
            size_t x = 0;

            for (size_t j = i; j < len && j - i < row_len; j++) {
                if (extended_pattern[j] == row[j - i]) {
                    correct++;
                    continue;
                } else {
                    incorrect++;
                    x = j - i;
                }

                if (incorrect == 2)
                    break;
            }

            if (incorrect == 0)
                break;

            if (incorrect == 1) {
                printf("(%zu,%zu)\n", x, y);

                return EXIT_SUCCESS;
            }
        }
    }

    return EXIT_FAILURE;
}
