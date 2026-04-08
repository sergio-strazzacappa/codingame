#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define MAX_EXPRESSION_SIZE 2048

int is_open_bracket(char c) {
    return (c == '(' || c == '[' || c == '{');
}

int is_close_bracket(char c) {
    return (c == ')' || c == ']' || c == '}');
}

int correct_bracket(char c1, char c2) {
    switch (c1) {
        case '(':
            if (c2 == ')')  return 1;
            else            return 0;
            break;
        case '[':
            if (c2 == ']')  return 1;
            else            return 0;
            break;
        case '{':
            if (c2 == '}')  return 1;
            else            return 0;
            break;
        default:
            return 0;
            break;
    }
}

void solve(char expression[]) {
    char stack[MAX_EXPRESSION_SIZE];
    size_t count = 0;
    size_t len = strlen(expression);

    for (size_t i = 0; i < len; i++) {
        char c = expression[i];

        if (!is_open_bracket(c) && !is_close_bracket(c))
            continue;
        if (is_open_bracket(c))
            stack[count++] = c;
        if (is_close_bracket(c)) {
            char top = stack[count - 1];
            if (correct_bracket(top, c))
                count--;
            else {
                printf("false\n");
                return;
            }
        }
    }

    if (count == 0) printf("true\n");
    else            printf("false\n");
}

int main(void) {
    char expression[MAX_EXPRESSION_SIZE + 1] = "";
    scanf("%s", expression);

    solve(expression);

    return 0;
}
