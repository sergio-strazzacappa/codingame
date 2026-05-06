#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ROOMS 23

enum Position {
    NONE,
    TOP,
    LEFT,
    RIGHT
};

struct ROOM {
    int type;
    enum Position entry_point;
    int delta_x;
    int delta_y;
};

const struct ROOM ROOMS[NUM_ROOMS] = {
    {0,     NONE,   +0, +0},
    {1,     LEFT,   +0, +1},
    {1,     TOP,    +0, +1},
    {1,     RIGHT,  +0, +1},
    {2,     LEFT,   +1, +0},
    {2,     RIGHT,  -1, +0},
    {3,     TOP,    +0, +1},
    {4,     TOP,    -1, +0},
    {4,     RIGHT,  +0, +1},
    {5,     LEFT,   +0, +1},
    {5,     TOP,    +1, +0},
    {6,     LEFT,   +1, +0},
    {6,     RIGHT,  -1, +0},
    {7,     TOP,    +0, +1},
    {7,     RIGHT,  +0, +1},
    {8,     LEFT,   +0, +1},
    {8,     RIGHT,  +0, +1},
    {9,     LEFT,   +0, +1},
    {9,     TOP,    +0, +1},
    {10,    TOP,    -1, +0},
    {11,    TOP,    +1, +0},
    {12,    RIGHT,  +0, +1},
    {13,    LEFT,   +0, +1}
};

void init();
void game();
void clean();
void debug();

int rows;
int cols;
int **grid;

int main() {
    init();
    game();
    debug();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &cols, &rows);
    fgetc(stdin);

    grid = (int **)malloc(sizeof(int*) * rows);

    for (int y = 0; y < rows; y++) {
        char line[201];
        scanf("%[^\n]", line);
        fgetc(stdin);

        grid[y] = (int *)malloc(sizeof(int) * cols);

        char string_type[3] = "";
        int index = 0;
        int x = 0;

        for (int i = 0; i < strlen(line); i++) {
            if (line[i] == ' ') {
                string_type[index++] = '\0';
                grid[y][x++] = atoi(string_type);
                index = 0;
                continue;
            }
            string_type[index++] = line[i];
        }

        string_type[index++] = '\0';
        grid[y][x++] = atoi(string_type);
    }

    // ignore in this level
    int ex;
    scanf("%d", &ex);
}

void game() {
    while (1) {
        int current_x;
        int current_y;
        char pos[6];
        
        scanf("%d%d%s", &current_x, &current_y, pos);

        int room_type = grid[current_y][current_x];
        enum Position entry = NONE;

        if (strcmp(pos, "TOP") == 0)
            entry = TOP;
        else if (strcmp(pos, "LEFT") == 0)
            entry = LEFT;
        else if (strcmp(pos, "RIGHT") == 0)
            entry = RIGHT;
        else
            fprintf(stderr, "[ERROR] Incorrect position\n");

        int next_x = current_x;
        int next_y = current_y;

        fprintf(stderr, "[DEBUG] room type = %d, entry = %d\n", room_type, entry);

        for (int i = 0; i < NUM_ROOMS; i++) {
            if (room_type == ROOMS[i].type && entry == ROOMS[i].entry_point) {
                fprintf(stderr, "[DEBUG] ROOM FOUND\n");
                next_x = current_x += ROOMS[i].delta_x;
                next_y = current_y += ROOMS[i].delta_y;
                break;
            }
        }

        printf("%d %d\n", next_x, next_y);
    }
}

void clean() {
    for (int y = 0; y < rows; y++)
        free(grid[y]);
    free(grid);
}

void debug() {
    fprintf(stderr, "[DEBUG] Size of the grid = %dX%d\n", rows, cols);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            fprintf(stderr, "%3d", grid[y][x]);
        }
        fprintf(stderr, "\n");
    }
}
