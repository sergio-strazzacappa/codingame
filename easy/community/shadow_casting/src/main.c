#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void solve(char lines[3][257]);

int main() {
    int n;

    scanf("%d", &n);
    fgetc(stdin);

    char lines[3][257];

    for (int i = 0; i < 3; i++)
        lines[i][0] = '\0';

    for (int i = 0; i < n; i++) {
        lines[0][0] = '\0';
        scanf("%[^\n]", lines[0]);
        fgetc(stdin);

        solve(lines);

        strcpy(lines[2], lines[1]);
        strcpy(lines[1], lines[0]);
    }

    size_t i = 0;
    for (; i < strlen(lines[0]); i++)
        lines[0][i] = ' ';
    lines[0][i] = '\0';

    solve(lines);
    strcpy(lines[2], lines[1]);
    strcpy(lines[1], lines[0]);
    solve(lines);

    return 0;
}

void solve(char lines[3][257]) {
    int len = (int)strlen(lines[0]);

    for (int i = 0; i < len; i++) {
        // if the current char is not blank, copy it to output
        if (lines[0][i] != ' ') {
            printf("%c", lines[0][i]);
            continue;
        }

        // check the previous line for hyphen shadow
        if (i > 0 && lines[1][0] != '\0' && i - 1 < strlen(lines[1]) && lines[1][i - 1] != ' ') {
            printf("%c", '-');
            continue;
        }

        // check the previous of the previous line for backtick shadow
        if (i > 1 && lines[2][0] != '\0' && i - 2 < strlen(lines[2]) && lines[2][i - 2] != ' ') {
            printf("%c", '`');
            continue;
        }

        printf("%c", lines[0][i]);
    }

    // check for shadow at the right of the text
    for (int i = len - 1; i < (int)MAX(strlen(lines[1]), strlen(lines[2]) + 1); i++) {
        if (i < 0 && lines[1][0] != '\0')
            printf("%s", " ");
        if (i < strlen(lines[1]) && lines[1][i] != ' ') {
            printf("%s", "-");
        } else if (lines[2][0] != '\0' && i > 0 && lines[2][i - 1] != ' ') {
            printf("%s", "`");
        } else if (i < MAX(strlen(lines[1]), strlen(lines[2]) + 1) - 1)
            printf("%s", " ");
    }

    printf("\n");
}
