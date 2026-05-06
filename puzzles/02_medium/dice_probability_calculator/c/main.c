#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 500

enum operation {
    MULTIPLICATION,
    ADDITION,
    SUBSTRACTION,
    GREATER_THAN
};

struct operand {
    int     values[SIZE];
    float   probs[SIZE];
    int     size;
};

struct operand parse(char expr[]);
struct operand solve(
    struct operand operands[], enum operation operators[], int index);
void sort(struct operand *op);
void swapi(int *x, int *y);
void swapf(float *x, float *y);

int main() {
    char expr[101];
    scanf("%[^\n]", expr);
    struct operand result = parse(expr);

    // sort the result in ascending order by values
    sort(&result);

    for (int i = 0; i < result.size; i++)
        printf("%d %.2f\n", result.values[i], result.probs[i] * 100);

    return 0;
}

 struct operand parse(char expr[]) {
    int len = strlen(expr);

    enum operation operators[SIZE];
    int operators_index = 0;

    struct operand operands[SIZE];
    int operands_index = 0;

    int current_operator = 0;
    bool die = false;

    char subexpr[SIZE];
    int subexpr_index = 0;
    bool in_subexpr = false;
    bool skip = false;

    for (int i = 0; i < len; i++) {
        char c = expr[i];

        if (c == '(') {
            // start of a subexpresion, mark to start storing
            in_subexpr = true;
            subexpr[0] = '\0';
            subexpr_index = 0;
            continue;
        }

        if (c == ')') {
            // end of a subexpresion, parse it
            in_subexpr = false;
            skip = true;
            operands[operands_index++] = parse(subexpr); 
            continue;
        }

        if (in_subexpr) {
            // still in subexpresion, store the char
            subexpr[subexpr_index++] = c;
            subexpr[subexpr_index] = '\0';
            continue;
        }

        if (c >= '0' && c <= '9') {
            // in a constant, make the number
            current_operator *= 10;
            current_operator += c - '0';

            if (i < len - 1)
                continue;
        }

        if (c == 'd') {
            // mark if it is a die
            die = true;
            continue;
        }

        if (c == '*')   operators[operators_index++] = MULTIPLICATION;
        if (c == '+')   operators[operators_index++] = ADDITION;
        if (c == '-')   operators[operators_index++] = SUBSTRACTION;
        if (c == '>')   operators[operators_index++] = GREATER_THAN;

        if (skip) {
            // if it was a subexpresion (between parenthesis), the result was
            // store previously, jump to the next iteration
            skip = false;
            continue;
        }

        if (die) {
            // if it is a die, save every possible value
            struct operand op;
            op.size = current_operator;

            for (int i = 0; i < current_operator; i++) {
                op.values[i] = i + 1;
                op.probs[i] = 1. / current_operator;
            }

            operands[operands_index++] = op;
        } else {
            // it is a constant, save it only value
            struct operand op = {
                .values[0] = current_operator,
                .probs[0] = 1,
                .size = 1
            };

            operands[operands_index++] = op; 
        }
        die = false;
        current_operator = 0;
    }

    // solve the expresion and return the result
    return solve(operands, operators, operators_index);
}

struct operand solve(
    struct operand operands[], enum operation operators[], int index) {

    struct operand result;
    result.size = 0;
    enum operation current_operator = MULTIPLICATION;

    while (index > 0) {
        // exit when there is no operation left
        for (int i = 0; i < index; i++) {
            result.size = 0;
            struct operand op1 = operands[i];
            struct operand op2 = operands[i + 1];
            enum operation operator = operators[i]; 

            if (operator != current_operator)
                // jump to the next operation if it is not the one with
                // highest priority
                continue;

            for (int j = 0; j < op1.size; j++) {
                for (int k = 0; k < op2.size; k++) {
                    // compute the results
                    int r = 0;

                    if (operator == MULTIPLICATION) r = op1.values[j] * op2.values[k];
                    if (operator == ADDITION)       r = op1.values[j] + op2.values[k];
                    if (operator == SUBSTRACTION)   r = op1.values[j] - op2.values[k];
                    if (operator == GREATER_THAN)   r = op1.values[j] > op2.values[k] ? 1 : 0;

                    // if it was already computed update its probability
                    bool found = false;
                    for (int l = 0; l < result.size; l++) {
                        if (r == result.values[l]) {
                            result.probs[l] += op1.probs[j] * op2.probs[k];
                            found = true;
                            break;
                        }
                    }

                    // if not found save it as a new entry
                    if (!found) {
                        result.values[result.size] = r;
                        result.probs[result.size] = op1.probs[j] * op2.probs[k];
                        result.size++;
                    }
                }
            }

            // remove the current operator
            for (int j = 0; j < index - 1; j++) {
                if (j >= i)
                    operators[j] = operators[j + 1];
            }

            // update the operand
            for (int j = 0; j < index; j++) {
                if (j == i)
                    operands[j] = result;
                if (j > i)
                    operands[j] = operands[j + 1];
            }

            index--;
            i = -1;
        }
        current_operator++;
    }

    return result;
}

// sort the result in ascending order by value
void sort(struct operand *op) {
    bool swapped;

    for (int i = 0; i < op->size - 1; i++) {
        swapped = false;
        for (int j = 0; j < op->size - i - 1; j++) {
            if (op->values[j] > op->values[j + 1]) {
                swapi(&op->values[j], &op->values[j + 1]);
                swapf(&op->probs[j], &op->probs[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// swap integer values
void swapi(int *x, int *y) {
    float temp = *x;
    *x = *y;
    *y = temp;
}

// swap floating-point values
void swapf(float *x, float *y) {
    float temp = *x;
    *x = *y;
    *y = temp;
}
