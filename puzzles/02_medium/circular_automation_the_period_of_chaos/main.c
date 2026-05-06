#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEST            0
#define NUMBER_FILES    7

char *input_files[] = {
    "input/01_simple_example.txt",
    "input/02_blinker.txt",
    "input/03_rule_250_mix.txt",
    "input/04_126=fractal.txt",
    "input/05_so_long.txt",
    "input/06_rule_110.txt",
    "input/07_where_is_the_motif.txt",
};

char *output_files[] = {
    "output/01_simple_example.txt",
    "output/02_blinker.txt",
    "output/03_rule_250_mix.txt",
    "output/04_126=fractal.txt",
    "output/05_so_long.txt",
    "output/06_rule_110.txt",
    "output/07_where_is_the_motif.txt",
};

int line_length;
int max_iter;
int rule_number;

int solve();
void get_line(char next_line[], int j, char prev, char cur, char next, int binary[]);
void dump_input();

int main() {
    if (TEST) {
        // read from the files
        for (int i = 0; i < NUMBER_FILES; i++) {
            FILE *fp;
            char line[10];
            int result;

            if ((fp = fopen(input_files[i], "r")) == NULL) {
                printf("[ERROR] Can't open file %s\n", input_files[i]);
                exit(1);
            }

            fgets(line, 10, fp); line_length    = atoi(line);
            fgets(line, 10, fp); max_iter       = atoi(line);
            fgets(line, 10, fp); rule_number    = atoi(line);

            int period = solve();

            fclose(fp);

            if ((fp = fopen(output_files[i], "r")) == NULL) {
                printf("[ERROR] Can't open file %s\n", output_files[i]);
                exit(1);
            }

            fgets(line, 10, fp);

            if (strcmp(line, "BIG\n") == 0)
                result = -1;
            else
                result = atoi(line);

            printf("%s\n", period == result ? "PASSED" : "FAILED");
            fclose(fp);
        }
    } else {
        // read from the std input
        scanf("%d%d%d", &line_length, &max_iter, &rule_number);

        int period = solve();

        if (period != -1)
            printf("%d\n", period);
        else
            printf("BIG\n");
    }
    return 0;
}

// returns -1 if period is BIG
int solve() {
    char line[line_length + 1];
    int binary[8];

    // set the starting line
    for (int i = 0; i < line_length; i++) {
        line[i] = '.';
    }
    line[line_length] = '\0';
    line[line_length / 2] = '1';

    // get the binary form of the rule
    int i = 7;
    while (rule_number > 0) {
        binary[i--] = rule_number % 2;
        rule_number /= 2;
    }

    for (; i >= 0; i--) {
        binary[i] = 0;
    }

    char *history[max_iter];
    int index = 0;
    int left = 0;
    int right = 0;
    int period = 0;

    for (int i = 0; i < max_iter; i++) {
        char next_line[line_length + 1];
        history[index] = (char *)malloc(sizeof(char) * (line_length + 1));     
        strcpy(history[index], line);

        fprintf(stderr, "%s\n", history[index]);

        index++;

        // calculate the next iteration
        for (int j = 0; j < line_length; j++) {
            if (j == 0) {
                get_line(next_line, j, line[line_length - 1], line[j], line[j + 1], binary);
                continue;
            }
            if (j == (line_length - 1)) {
                get_line(next_line, j, line[j - 1], line[j], line[0], binary);
                continue;
            }
            get_line(next_line, j, line[j - 1], line[j], line[j + 1], binary);
        }
        next_line[line_length] = '\0';

        // check for the period
        if (!left) {
            for (int j = 0; j < i; j++) {
                if (strcmp(history[j], line) == 0) {
                    // left line found 
                    char *temp[max_iter];
                    left = 1;
                    index = 0;
                    
                    for (int k = j; k < i; k++) {
                        temp[index] = (char *)malloc(sizeof(char) * (line_length + 1));
                        strcpy(temp[index++], history[k]);
                    }
                    for (int k = 0; k < index; k++) {
                        strcpy(history[k], temp[k]);
                    }
                    period = index;
                    break;
                }
            }
        } else {
            // left line already found
            for (int j = 0; j < index; j++) {
                if (strcmp(history[j], next_line) == 0) {
                    right = 1;
                    break;
                }
            }
            if (!right)
                period++;
        }

        if (right)
            break;

        strcpy(line, next_line);
    }
    
    if (!right)
        return -1;

    return period;
}

void get_line(char next_line[], int j, char prev, char cur, char next, int binary[]) {
    if (prev == '1' && cur == '1' && next == '1') {
        binary[0] == 1 ? (next_line[j] = '1') : (next_line[j] = '.'); 
        return;
    }
    if (prev == '1' && cur == '1' && next == '.') {
        binary[1] == 1 ? (next_line[j] = '1') : (next_line[j] = '.'); 
        return;
    }
    if (prev == '1' && cur == '.' && next == '1') {
        binary[2] == 1 ? (next_line[j] = '1') : (next_line[j] = '.'); 
        return;
    }
    if (prev == '1' && cur == '.' && next == '.') {
        binary[3] == 1 ? (next_line[j] = '1') : (next_line[j] = '.'); 
        return;
    }
    if (prev == '.' && cur == '1' && next == '1') {
        binary[4] == 1 ? (next_line[j] = '1') : (next_line[j] = '.'); 
        return;
    }
    if (prev == '.' && cur == '1' && next == '.') {
        binary[5] == 1 ? (next_line[j] = '1') : (next_line[j] = '.'); 
        return;
    }
    if (prev == '.' && cur == '.' && next == '1') {
        binary[6] == 1 ? (next_line[j] = '1') : (next_line[j] = '.'); 
        return;
    }
    if (prev == '.' && cur == '.' && next == '.') {
        binary[7] == 1 ? (next_line[j] = '1') : (next_line[j] = '.'); 
        return;
    }
}

void dump_input() {
    printf("The line length is: %d\n", line_length);
    printf("The maximum iterations is: %d\n", max_iter);
    printf("The rule number is: %d\n", rule_number);
}
