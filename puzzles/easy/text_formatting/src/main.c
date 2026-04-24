#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1000

bool is_punctuation_mark(const char c) {
    return (c != ' ' && !isalnum(c));
}

void solve(const char text[]) {
    size_t len = strlen(text);
    bool is_upper = true;
    char last_punct_mark = ' ';

    for (size_t i = 0; i < len; i++) {
        char c = text[i];

        // remove extra whitespaces
        if (c == ' ' && i < len - 1 &&
            (text[i + 1] == ' ' || is_punctuation_mark(text[i + 1])))
                continue;

         // remove repeated punctuation marks
        if (is_punctuation_mark(c) && c == last_punct_mark) {
            if (i < len - 1 && isalpha(text[i + 1]))
                putchar(' ');
            continue;
        }

        // print the case of a letter
        if (isalpha(c)) {
            last_punct_mark = ' ';
            if (is_upper) {
                putchar(toupper(c));
                is_upper = false;
                continue;
            } else
                putchar(tolower(c));
            continue;
        }

        if (is_punctuation_mark(c) && c != last_punct_mark) {
            last_punct_mark = c;

            if (c == '.')
                is_upper = true;

            putchar(c);

            // print whitespace between a punctuation mark and a letter
            if (i < len - 1 && isalpha(text[i + 1]))
                putchar(' ');
            continue;
        }

        putchar(c);
    }
}

int main(void) {
    char text[SIZE + 1];

    if (fgets(text, sizeof(text), stdin) == NULL) {
        fprintf(stderr, "[ERROR] Can't read input from stdin\n");
        return EXIT_FAILURE;
    }

    text[strcspn(text, "\n")] = '\0';

    solve(text);

    return EXIT_SUCCESS;
}
