#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

void solve(const char buffer[]) {
    size_t len = strlen(buffer);
    size_t n_choices = 0;
    size_t current_choice = 0;
    size_t clause = 0;
    bool in_choice = false;

    for (size_t i = 0; i < len; i++) {
        if (buffer[i] != '(' && !in_choice) {
            putchar(buffer[i]);
            continue;
        }

        // select a choice
        if (buffer[i] == '(') {
            n_choices = 1;
            current_choice = 0;
            for (size_t j = i + 1; j < len && buffer[j] != ')'; j++) {
                if (buffer[j] == '|') {
                    n_choices++;
                }
            }
            in_choice = true;
            continue;
        }
        if (buffer[i] == ')') {
            in_choice = false;
            clause++;
            continue;
        }
        if (buffer[i] == '|') {
            current_choice++;
            continue;
        }
        if (current_choice == (clause % n_choices))
            putchar(buffer[i]);
    }
}

int main(void) {
    size_t n;
    scanf("%zu", &n);
    fgetc(stdin);
    char buffer[10001] = "";

    for (size_t i = 0; i < n; i++) {
        char line[10001];
        fgets(line, sizeof(line), stdin);
        strcat(buffer, line);
    }

    solve(buffer);

    return EXIT_SUCCESS;
}
