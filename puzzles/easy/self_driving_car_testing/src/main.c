#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define ROAD_SIZE 40

typedef struct instr_s {
    size_t moves;
    char dir;
} instr_t;

void solve(
    size_t *current_road, instr_t instrs[], size_t *current_index,
    char *pattern) {

    pattern[strcspn(pattern, "\n")] = '\0';
    size_t n = atoi(strtok(pattern, ";"));
    const char *road = strtok(NULL, "");

    for (size_t i = 0; i < n; i++) {
        // print the current line
        for (size_t j = 0; j < strlen(road); j++) {
            if (j == *current_road) {
                putchar('#');
                continue;
            }
            putchar(road[j]);
        }

        putchar('\n');

        // update the position
        instrs[*current_index].moves--;
        if (instrs[*current_index].moves == 0 ) {
            (*current_index)++;
        }

        instr_t ins = instrs[*current_index];
        if (ins.dir == 'L')
            (*current_road)--;
        else if (ins.dir == 'R')
            (*current_road)++;

    }
}

int main(void) {
    size_t current_road;
    instr_t instrs[128];
    size_t instrs_size = 0;

    size_t n;
    scanf("%zu", &n);
    fgetc(stdin);

    char commands[257];
    fgets(commands, sizeof(commands), stdin);
    commands[strcspn(commands, "\n")] = '\0';
    current_road = atoi(strtok(commands, ";"));
    current_road--; // 0-based
    const char *tok = strtok(NULL, ";");

    while (tok != NULL) {
        instr_t inst = {0};
        for (size_t i = 0; i < strlen(tok); i++) {
            if (isdigit(tok[i])) {
                inst.moves *= 10;
                inst.moves += tok[i] - '0';
            }
        }
        inst.dir = tok[strlen(tok) - 1];
        instrs[instrs_size++] = inst;
        tok = strtok(NULL, ";");
    }

    size_t current_index = 0;

    for (size_t i = 0; i < n; i++) {
        char pattern[257];
        fgets(pattern, sizeof(pattern), stdin);

        solve(&current_road, instrs, &current_index, pattern);
    }

    return EXIT_SUCCESS;
}
