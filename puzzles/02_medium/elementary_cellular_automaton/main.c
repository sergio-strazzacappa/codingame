#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST            0
#define NUMBER_FILES    5

const char *INPUT_FILES[] = {
    "input/01_pyramid.txt",
    "input/02_sierpinski_triangle.txt",
    "input/03_rule_30_conus_textile.txt",
    "input/04_sierpinski_triangle_continued.txt",
    "input/05_rule_110_different_start.txt",
};

const char *OUTPUT_FILES[] = {
    "output/01_pyramid.txt",
    "output/02_sierpinski_triangle.txt",
    "output/03_rule_30_conus_textile.txt",
    "output/04_sierpinski_triangle_continued.txt",
    "output/05_rule_110_different_start.txt",
};

int rule;
int iteration;
char start_pattern[51];

void solve(char result[10000]);
void get_line(char next_pattern[], int j, char prev, char cur, char next, int binary[]);

int main() {
    if (TEST) {
        for (int i = 0; i < NUMBER_FILES; i++) {
            FILE *fp;
            char line[100], result[10000], output[10000];
            result[0] = '\0';
            output[0] = '\0';

            if ((fp = fopen(INPUT_FILES[i], "r")) == NULL) {
                printf("[ERROR] Can't open file %s\n", INPUT_FILES[i]);
                exit(1);
            }

            fgets(line, 20, fp); rule = atoi(line);
            fgets(line, 20, fp); iteration = atoi(line);
            fgets(line, 51, fp); strcpy(start_pattern, line);
            start_pattern[strlen(start_pattern) - 1] = '\0';

            solve(result);

            fclose(fp);

            if ((fp = fopen(OUTPUT_FILES[i], "r")) == NULL) {
                printf("[ERROR] Can't open file %s\n", OUTPUT_FILES[i]);
                exit(1);
            }

            while (fgets(line, 51, fp)) {
                strcat(output, line);
            }

            printf("%s\n", strcmp(result, output) == 0 ? "PASSED" : "FAILED");

            fclose(fp);
        }

    } else {
        char result[10000];

        scanf("%d", &rule);
        scanf("%d", &iteration);
        scanf("%s", start_pattern);

        solve(result);

        printf("%s", result);
    }
    return 0;
}

void solve(char result[10000]) {
    char pattern[51], next_pattern[51];
    int binary[8];

    // copy the start pattern
    strcpy(pattern, start_pattern);

    // calculate the binary form of the rule
    int i = 7;
    while (rule > 0) {
        binary[i--] = rule % 2;
        rule /= 2;
    }

    for (; i >= 0; i--) {
        binary[i] = 0;
    }

    // process each iteration
    for (int i = 0; i < iteration; i++) {
        strcat(result, pattern);
        strcat(result, "\n");

        for (int j = 0; j < strlen(pattern); j++) {
            if (j == 0) {
                get_line(next_pattern, j, pattern[strlen(pattern) - 1], pattern[j], pattern[j + 1], binary);
                continue;
            }
            if (j == (strlen(pattern) - 1)) {
                get_line(next_pattern, j, pattern[j - 1], pattern[j], pattern[0], binary);
                continue;
            }
            get_line(next_pattern, j, pattern[j - 1], pattern[j], pattern[j + 1], binary);
        }
        next_pattern[strlen(pattern)] = '\0';
        strcpy(pattern, next_pattern);
    }
}

void get_line(char next_pattern[], int j, char prev, char cur, char next, int binary[]) {
    if (prev == '@' && cur == '@' && next == '@') {
        binary[0] == 1 ? (next_pattern[j] = '@') : (next_pattern[j] = '.');
        return;
    }
    if (prev == '@' && cur == '@' && next == '.') {
        binary[1] == 1 ? (next_pattern[j] = '@') : (next_pattern[j] = '.');
        return;
    }
    if (prev == '@' && cur == '.' && next == '@') {
        binary[2] == 1 ? (next_pattern[j] = '@') : (next_pattern[j] = '.');
        return;
    }
    if (prev == '@' && cur == '.' && next == '.') {
        binary[3] == 1 ? (next_pattern[j] = '@') : (next_pattern[j] = '.');
        return;
    }
    if (prev == '.' && cur == '@' && next == '@') {
        binary[4] == 1 ? (next_pattern[j] = '@') : (next_pattern[j] = '.');
        return;
    }
    if (prev == '.' && cur == '@' && next == '.') {
        binary[5] == 1 ? (next_pattern[j] = '@') : (next_pattern[j] = '.');
        return;
    }
    if (prev == '.' && cur == '.' && next == '@') {
        binary[6] == 1 ? (next_pattern[j] = '@') : (next_pattern[j] = '.');
        return;
    }
    if (prev == '.' && cur == '.' && next == '.') {
        binary[7] == 1 ? (next_pattern[j] = '@') : (next_pattern[j] = '.');
        return;
    }
}
