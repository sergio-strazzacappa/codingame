#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

const int DIRS[4][2] = {
    { +1, +0 }, // >
    { +0, +1 }, // v
    { -1, +0 }, // <
    { +0, -1 }  // ^
};

typedef struct pika_s {
    size_t x;
    size_t y;
    char dir;
} pika_t;

bool is_wall(int x, int y, char **grid, size_t rows, size_t cols) {
    return (x < 0 || x > (int)cols - 1 ||
            y < 0 || y > (int)rows - 1 ||
            grid[y][x] == '#');
}

int turn_left(
    int *next_index,
    int *next_x, int *next_y,
    char **grid, size_t rows, size_t cols) {

    (*next_index)++;

    if (*next_index == 4)
        *next_index = 0;

    *next_x = *next_x + DIRS[*next_index][0];
    *next_y = *next_y + DIRS[*next_index][1];

    return !(is_wall(*next_x, *next_y, grid, rows, cols));
}

int turn_right(
    int *next_index,
    int *next_x, int *next_y,
    char **grid, size_t rows, size_t cols) {

    (*next_index)--;

    if (*next_index == -1)
        *next_index = 3;

    *next_x = *next_x + DIRS[*next_index][0];
    *next_y = *next_y + DIRS[*next_index][1];

    return !(is_wall(*next_x, *next_y, grid, rows, cols));
}

int go_back(
    int *next_index,
    int *next_x, int *next_y,
    char **grid, size_t rows, size_t cols) {

    if (*next_index == 0)
        *next_index = 2;
    else if (*next_index == 1)
        *next_index = 3;
    else if (*next_index == 2)
        *next_index = 0;
    else
        *next_index = 1;

    *next_x = *next_x + DIRS[*next_index][0];
    *next_y = *next_y + DIRS[*next_index][1];

    return !(is_wall(*next_x, *next_y, grid, rows, cols));
}

void solve(char **grid, size_t rows, size_t cols, const char *side) {
    bool found = false;
    pika_t start = {0};

    // find the starting position and direction
    for (size_t y = 0; y < rows && !found; y++) {
        for (size_t x = 0; x < cols; x++) {
            if (grid[y][x] != '0' && grid[y][x] != '#') {
                start.x = x;
                start.y = y;
                start.dir = grid[y][x];
                grid[y][x] = '0';
                found = true;
                break;
            }
        }
    }

    // simulate the moves
    pika_t current = start;
    int index = -1;
    switch (start.dir) {
        case '>':
            index = 0;
            break;
        case 'v':
            index = 1;
            break;
        case '<':
            index = 2;
            break;
        case '^':
            index = 3;
            break;
        default:
            assert(false);
            break;
    }

    bool moved = true;
    do {
        int next_index = index;
        int next_x = current.x;
        int next_y = current.y;
        moved = true;

        if (side[0] == 'L') {
            if (!turn_right(&next_index, &next_x, &next_y, grid, rows, cols)) {
                next_x = (int)current.x + DIRS[index][0];
                next_y = (int)current.y + DIRS[index][1];
                next_index = index;

                if (is_wall(next_x, next_y, grid, rows, cols)) {
                    next_x = current.x;
                    next_y = current.y;
                    if (!turn_left(&next_index, &next_x, &next_y, grid, rows, cols)) {
                        next_x = current.x;
                        next_y = current.y;
                        next_index = index;
                        if (!go_back(&next_index, &next_x, &next_y, grid, rows, cols))
                            moved = false;
                    }
                }
            }
        } else if (side[0] == 'R') {
            if (!turn_left(&next_index, &next_x, &next_y, grid, rows, cols)) {
                next_x = (int)current.x + DIRS[index][0];
                next_y = (int)current.y + DIRS[index][1];
                next_index = index;

                if (is_wall(next_x, next_y, grid, rows, cols)) {
                    next_x = current.x;
                    next_y = current.y;
                    if (!turn_right(&next_index, &next_x, &next_y, grid, rows, cols)) {
                        next_x = current.x;
                        next_y = current.y;
                        next_index = index;
                        if (!go_back(&next_index, &next_x, &next_y, grid, rows, cols))
                            moved = false;
                    }
                }
            }
        }

        if (moved) {
            // go forward one step
            grid[next_y][next_x]++;
            current.x = next_x;
            current.y = next_y;
            index = next_index;
        }
    } while ((current.x != start.x || current.y != start.y) && moved);
}

int main(void) {
    size_t rows, cols;
    scanf("%zu %zu", &cols, &rows);
    fgetc(stdin);

    char **grid = (char **)calloc(rows, sizeof(char *));

    for (size_t y = 0; y < rows; y++) {
        grid[y] = (char *)calloc(cols + 2, sizeof(char));

        fgets(grid[y], cols + 2, stdin);
    }

    char side[2];
    fgets(side, 2, stdin);

    solve(grid, rows, cols, side);

    for (size_t y = 0; y < rows; y++)
        printf("%s", grid[y]);

    for (size_t y = 0; y < rows; y++)
        free(grid[y]);
    free(grid);

    return EXIT_SUCCESS;
}
