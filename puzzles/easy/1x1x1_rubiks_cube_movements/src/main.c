#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

// x: F -> U -> B -> D
// y: F -> L -> B -> R
// z: U -> R -> D -> L

void rotate(int move, char dir, char *face1, char *face2) {
    fprintf(stderr, "[DEBUG] rotate(%d, %c, %c, %c)\n", move, dir, *face1, *face2);

    char *cycle = NULL;

    if (dir == 'x')
        cycle = "FUBD";
    if (dir == 'y')
        cycle = "FLBR";
    if (dir == 'z')
        cycle = "URDL";

    assert(cycle != NULL);

    const char *p1 = strchr(cycle, *face1);

    if (p1 != NULL) {
        int index = (int)(p1 - cycle);
        index += move;
        index = ((index % 4) + 4) % 4;
        *face1 = cycle[index];
    }

    const char *p2 = strchr(cycle, *face2);

    if (p2 != NULL) {
        int index = (int)(p2 - cycle);
        index += move;
        index = ((index % 4) + 4) % 4;
        *face2 = cycle[index];
    }
}

void solve(char rotations[], char face1, char face2) {
    char *tok = strtok(rotations, " ");

    while (tok != NULL) {
        if (strlen(tok) == 1)
            rotate(1, tok[0], &face1, &face2);
        else
            rotate(-1, tok[0], &face1, &face2);

         tok = strtok(NULL, " ");
    }

    printf("%c\n%c\n", face1, face2);
}

int main(void) {
    char rotations[101], face1, face2;

    fgets(rotations, sizeof(rotations), stdin);
    rotations[strcspn(rotations, "\n")] = '\0';

    face1 = getchar(); getchar();
    face2 = getchar(); getchar();

    solve(rotations, face1, face2);

    return EXIT_SUCCESS;
}
