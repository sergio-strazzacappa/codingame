#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1025

void input();
void solve();
int syntax_error();
void clear();

int array_size;
char* program;
int* inputs;

int main() {
    input();
    solve();
    clear();
    return 0;
}

void input() {
    int line_count, input_count;
    scanf("%d%d%d", &line_count, &array_size, &input_count);
    fgetc(stdin);

    // read the brainfuck program
    program = malloc(line_count * LINE_SIZE * sizeof(char));
    int byte = 0;

    for (int i = 0; i < line_count; i++) {
        char line[LINE_SIZE];
        scanf("%[^\n]", line);
        fgetc(stdin);

        for (int j = 0; j < LINE_SIZE; j++) {
            if (line[j] == '\0') {
                break;
            }
            program[byte] = line[j];
            byte++;
        }
    }

    // read the input
    inputs = malloc(input_count * sizeof(int));
    for (int i = 0; i < input_count; i++) {
        scanf("%d", &inputs[i]);
    }
}

void solve() {
    if (!syntax_error()) {
        int array[array_size];
        int *ptr = array; // ptr -> array[0]
        int input_to_read = 0;
        int position = 0;

        for (int i = 0; i < array_size; i++) {
            array[i] = 0;
        }

        for (int i = 0; i < strlen(program); i++) {
            fprintf(stderr, "PC: %d - %c\n", i, program[i]);
            if (program[i] == '>') {
                ++ptr;
                ++position;
                fprintf(stderr, "[DEBUG] %d\n", *ptr);
            } else if (program[i] == '<') {
                --ptr;
                --position;
                fprintf(stderr, "[DEBUG] %d\n", *ptr);
            } else if (program[i] == '+') {
                ++*ptr;
                if (*ptr > 255) {
                    printf("INCORRECT VALUE\n");
                    break;
                }
                fprintf(stderr, "[DEBUG] %d\n", *ptr);
            } else if (program[i] == '-') {
                --*ptr;
                if (*ptr < 0) {
                    printf("INCORRECT VALUE\n");
                    break;
                }
                fprintf(stderr, "[DEBUG] %d\n", *ptr);
            } else if (program[i] == '.') {
                putchar(*ptr);
                fprintf(stderr, "[DEBUG] PRINT: %d %c\n", *ptr, *ptr);
            } else if (program[i] == ',') {
                *ptr = inputs[input_to_read];
                input_to_read++;
                fprintf(stderr, "[DEBUG] READ: %d %c\n", *ptr, *ptr);
            } else if (program[i] == '[' && !*ptr) {
                int quantity = 0;
                for (int j = i + 1; j < strlen(program); j++) {
                    if (program[j] == '[') {
                        quantity++;
                    }
                    if (program[j] == ']') {
                        if (!quantity) {
                            i = j;
                            break;
                        } else {
                            quantity--;
                        }
                    }
                }
            } else if (program[i] == ']' && *ptr) {
                int quantity = 0;
                for (int j = i - 1; j >= 0; j--) {
                    if (program[j] == ']') {
                        quantity++;
                    }
                    if (program[j] == '[') {
                        if (!quantity) {
                            i = j;
                            break;
                        } else {
                            quantity--;
                        }
                    }
                }
            }
            fprintf(stderr, "[DEBUG] ptr: %d\n", position);
            if (position < 0 || position > (array_size - 1)) {
                printf("POINTER OUT OF BOUNDS\n");
                break;
            }
        }
    }
}

int syntax_error() {
    int open, close;
    open = close = 0;

    for (int i = 0; i < strlen(program); i++) {
        if (program[i] == '[') {
            open++;
        }
        if (program[i] == ']') {
            close++;
        }
    }
    if (open != close) {
        printf("SYNTAX ERROR\n");
        return 1;
    }
    return 0;
}

void clear() {
    free(program);
    free(inputs);
}