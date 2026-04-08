#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define SEQUENCE_MAX_SIZE 300
#define N_LETTERS 26

void solve(char sequence[]) {
    float weights[N_LETTERS];
    for (size_t i = 0; i < 26; i++)
        weights[i] = 0;

    int depth = 1;
    float max_weight = 0;
    int is_open_tag = true;
    char solution;

    for (size_t i = 0; i < strlen(sequence); i++) {
        char c = sequence[i];

        if (is_open_tag && isalpha(c)) {
            // found a new open tag
            depth++;
        } else if (!is_open_tag && isalpha(c)) {
            // found a close tag
            weights[c - 'a'] += 1. / depth;
            depth--;
            is_open_tag = true;
        } else {
            // the next tag is a close tag
            is_open_tag = false;
        }
    }

    // print the result
    for (size_t i = 0; i < N_LETTERS; i++) {
        if (weights[i] > max_weight) {
            max_weight = weights[i];
            solution = i + 'a';
        }
    }

    printf("%c\n", solution);
}

int main(void) {
    char sequence[SEQUENCE_MAX_SIZE + 1];
    scanf("%[^\n]", sequence);

    solve(sequence);

    return EXIT_SUCCESS;
}
