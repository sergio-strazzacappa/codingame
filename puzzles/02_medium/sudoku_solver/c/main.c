#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Point {
    int x;
    int y;
};

int **grid;
struct Point missing[81];
int missing_size;

void init();
void solve();
void backtracking(int **grid, struct Point p, int index, int start);
int get_missing_number(int start, struct Point p, int **grid);
int is_completed(int **grid);
void clean();
void debug();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    grid = (int **)malloc(sizeof(int *) * 9);

    for (int y = 0; y < 9; y++) {
        grid[y] = (int *)malloc(sizeof(int) * 9);
        char line[10];
        scanf("%[^\n]", line);
        fgetc(stdin);

        for (int x = 0; x < 9; x++) {
            grid[y][x] = line[x] - '0';

            // count the missing numbers
            if (grid[y][x] == 0) {
                struct Point p = {x, y};
                missing[missing_size++] = p;
            }
        }
    }
}

void solve() {
    struct Point p = missing[0];
    backtracking(grid, p, 0, 0);

    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            printf("%d", grid[y][x]);
        }
        printf("\n");
    }
}

void backtracking(int **grid, struct Point p, int index, int start) {
    /*
    debug();
    fprintf(stderr, "\n");
    fprintf(stderr, "[DEBUG] backtracking (%d, %d) - index=%d\n", p.x, p.y, index);
    sleep(1);
    */

    int n = get_missing_number(start, p, grid);

    if (n != -1) {
        grid[p.y][p.x] = n;
        //fprintf(stderr, "[DEBUG] Found n=%d\n", n);
        backtracking(grid, missing[index + 1], index + 1, 0);
    } else {
        return;
    } 

    //fprintf(stderr, "[DEBUG] return backtracking (%d, %d) - index=%d\n", p.x, p.y, index);
    if (is_completed(grid)) {
        //fprintf(stderr, "[DEBUG] Is completed\n");
        return;
    } else {
        start = n;
        grid[p.y][p.x] = 0;
        backtracking(grid, p, index, start);
    }
}

// return the first missing number greater than start in a cell, return -1
// if it is impossible to satisfy the constraints
int get_missing_number(int start, struct Point p, int **grid) {
    //fprintf(stderr, "[DEBUG] get_missing_number(%d, %d, %d)\n", start, p.x, p.y);
    int number = -1;
    int possible_numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // search in a row
    for (int x = 0; x < 9; x++) {
        if (grid[p.y][x] > 0) {
            possible_numbers[grid[p.y][x] - 1] = 0;
        }
    }

    // search in a col
    for (int y = 0; y < 9; y++) {
        if (grid[y][p.x] > 0) {
            possible_numbers[grid[y][p.x] - 1] = 0;
        }
    }

    // search in the 3x3 subgrid
    int x_subgrid = p.x / 3;
    int y_subgrid = p.y / 3;
    for (int y = y_subgrid * 3; y < y_subgrid * 3 + 3; y++) {
        for (int x = x_subgrid * 3; x < x_subgrid * 3 + 3; x++) {
            if (grid[y][x] > 0) {
                possible_numbers[grid[y][x] - 1] = 0;
            }
        }
    }
    
    for (int i = 0; i < 9; i++) {
        if (possible_numbers[i] > start) {
            number = possible_numbers[i];
            break;
        }
    }

    return number;
}

// return true if the grid is completed
int is_completed(int **grid) {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (grid[y][x] == 0)
                return 0;
        }
    }
    return 1;
}

void clean() {
    for (int y = 0; y < 9; y++)
        free(grid[y]);
    free(grid);
}

void debug() {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++)
            fprintf(stderr, "%d", grid[y][x]);
        fprintf(stderr, "\n");
    }
}
