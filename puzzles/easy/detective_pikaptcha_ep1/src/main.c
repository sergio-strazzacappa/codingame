#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

const int DIRS[4][2] = {
    { +1, +0 },
    { +0, +1 },
    { -1, +0 },
    { +0, -1 }
};

void solve(char **grid, size_t rows, size_t cols) {
    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            char ady = '0';

            if (grid[y][x] == '#')
                continue;

            for (size_t i = 0; i < 4; i++) {
                int ady_x = (int)x + DIRS[i][0];
                int ady_y = (int)y + DIRS[i][1];

                if (ady_x < 0 || ady_x > cols - 1)
                    continue;
                if (ady_y < 0 || ady_y > rows - 1)
                    continue;
                if (grid[ady_y][ady_x] != '#')
                    ady++;
            }
            grid[y][x] = ady;
        }
    }
}

int main(void) {
    size_t rows, cols;
    scanf("%zu%zu", &cols, &rows);
    fgetc(stdin);

    char **grid = (char **)calloc(rows, sizeof(char *));

    for (size_t y = 0; y < rows; y++) {
        grid[y] = (char *)calloc(cols + 2, sizeof(char));
        fgets(grid[y], cols + 2, stdin);
    }

    solve(grid, rows, cols);

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++)
            printf("%c", grid[y][x]);
        printf("\n");
    }

    for (size_t y = 0; y < rows; y++)
        free(grid[y]);
    free(grid);

    return EXIT_SUCCESS;
}
