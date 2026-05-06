#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RADIX 20

int l;
int h;
char **representation[RADIX];

struct operand {
    int h;
    int l;
    int decimal;
    char **representation;
} op1, op2;

char operation[2];

void init();
void solve();
int to_decimal(struct operand op);
int get_decimal(char **maya);
void to_maya(long d);
void clean();
void debug();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &l, &h);

    // parse the numercial system representation
    for (int i = 0; i < RADIX; i++) {
        representation[i] = (char **)malloc(sizeof(char *) * h);

        for (int j = 0; j < h; j++) {
            representation[i][j] = (char *)malloc(sizeof(char) * l + 1);
        }
    }

    for (int i = 0; i < h; i++) {
        char num[2049];
        scanf("%s", num);

        for (int j = 0; j < strlen(num); j++) {
            int n = j / l;

            representation[n][i][j % l] = num[j];
        }
        for (int j = 0; j < RADIX; j++)
            representation[j][i][l] = '\0';;
    }

    // parse the first operand
    scanf("%d", &op1.h);
    op1.l = l;
    op1.decimal = -1;

    op1.representation = (char **)malloc(sizeof(char *) * op1.h);

    for (int i = 0; i < op1.h; i++)
        op1.representation[i] = (char *)malloc(sizeof(char) * op1.l + 1);

    for (int i = 0; i < op1.h; i++)
        scanf("%s", op1.representation[i]);

    // parse the second operand
    scanf("%d", &op2.h);
    op2.l = l;
    op2.decimal = -1;

    op2.representation = (char **)malloc(sizeof(char *) * op2.h);

    for (int i = 0; i < op2.h; i++)
        op2.representation[i] = (char *)malloc(sizeof(char) * op2.l + 1);

    for (int i = 0; i < op2.h; i++)
        scanf("%s", op2.representation[i]);

    // read the operation
    scanf("%s", operation);
}

void solve() {
    op1.decimal = to_decimal(op1);
    op2.decimal = to_decimal(op2);

    if (operation[0] == '+')        to_maya((long)op1.decimal + op2.decimal);
    else if (operation[0] == '-')   to_maya((long)op1.decimal - op2.decimal);
    else if (operation[0] == '*')   to_maya((long)op1.decimal * op2.decimal);
    else if (operation[0] == '/')   to_maya((long)op1.decimal / op2.decimal);
    else                            fprintf(stderr, "[ERROR] Incorrect operation\n");

}

int to_decimal(struct operand op) {
    int decimal = 0;

    // representation of each number
    char **n = (char **)malloc(sizeof(char *) * h);

    for (int i = 0; i < h; i++)
        n[i] = (char *)malloc(sizeof(char) * l + 1);

    // exponent to raise the power
    int exp = op.h / h - 1;

    for (int i = 0; i < op.h / h; i++) {
        for (int j = 0; j < h; j++) {
            strcpy(n[j], op.representation[(i * h) + j]);
        }

        int d = get_decimal(n);
        decimal += d * pow(RADIX, exp);
        exp--;        
    }
    
    for (int i = 0; i < h; i++)
        free(n[i]);
    free(n);

    return decimal;
}

int get_decimal(char **maya) {
    for (int i = 0; i < RADIX; i++) {
        for (int j = 0; j < h; j++) {
            if (strcmp(maya[j], representation[i][j]) != 0) 
                break;
            if (j == h - 1)
                return i;
        }
    }
    fprintf(stderr, "[ERROR] Number not found\n");
    return -1;
}

void to_maya(long d) {
    // height of the result
    long n = d;
    int result_h = 0;

    do {
        n /= RADIX;
        result_h += h;
    } while (n > 0);

    char **output = (char **)malloc(sizeof(char *) * result_h);

    for (int i = 0; i < result_h; i++)
        output[i] = (char *)malloc(sizeof(char) * l + 1);

    int depth = 0;
    do {
        int n = d % RADIX;
        
        for (int i = 0; i < h; i++)
            strcpy(output[(depth * h) + i], representation[n][i]);

        d = d / RADIX;
        depth++;
    } while (d > 0);

    for (int i = depth - 1; i >= 0; i--) {
        for (int j = 0; j < h; j++) {
            printf("%s\n", output[i * h + j]);
        }
    }

    for (int i = 0; i < result_h; i++)
        free(output[i]);
    free(output);
}

void clean() {
    // clean the numerical system representation
    for (int i = 0; i < RADIX; i++) {
        for (int j = 0; j < h; j++) {
            free(representation[i][j]);
        }
        free(representation[i]);
    }

    // clean the first operand
    for (int i = 0; i < op1.h; i++)
        free(op1.representation[i]);
    free(op1.representation);

    // clean the second operand
    for (int i = 0; i < op2.h; i++)
        free(op2.representation[i]);
    free(op2.representation);
}

void debug() {
    fprintf(stderr, "[DEBUG] Length: %d Height: %d\n", l, h);

    for (int i = 0; i < RADIX; i++) {
        fprintf(stderr, "Number: %d\t", i);

        for (int j = 0; j < h; j++) {
            fprintf(stderr, "%s\n", representation[i][j]);
            if (j != h - 1)
                fprintf(stderr, "\t\t");
        }
    }

    fprintf(stderr, "[DEBUG] First operand\n");

    for (int i = 0; i < op1.h; i++)
        fprintf(stderr, "%s\n", op1.representation[i]);

    fprintf(stderr, "[DEBUG] Second operand\n");

    for (int i = 0; i < op2.h; i++)
        fprintf(stderr, "%s\n", op2.representation[i]);

    fprintf(stderr, "[DEBUG] Operation: %s\n", operation);
}
