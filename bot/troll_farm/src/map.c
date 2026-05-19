#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "map.h"
#include "entities.h"

const int DIRS[4][2] = {
    { +0, -1 },
    { +1, +0 },
    { +0, +1 },
    { -1, +0 }
};

size_t rows;
size_t cols;
char grid[MAX_HEIGHT][MAX_WIDTH];

void map_init(void) {
    scanf("%zu%zu", &cols, &rows);
    fgetc(stdin);

    for (size_t y = 0; y < rows; y++) {
        char line[cols + 2];
        fgets(line, sizeof(line), stdin);

        for (size_t x = 0; x < cols; x++) {
            grid[y][x] = line[x];

            if (line[x] == '0') {
                my_shack.x = x;
                my_shack.y = y;
            }
        }
    }
}

void map_print(void) {
    // spaces for the rows-index
    fprintf(stderr, "   ");

    // cols index
    for (size_t x = 0; x < cols; x++) {
        fprintf(stderr, "%3zu", x);
    }

    // separator of index and data
    fprintf(stderr, "\n----");

    for (size_t x = 0; x < cols; x++) {
        fprintf(stderr, "---");
    }

    fprintf(stderr, "\n");

    // print the map
    for (size_t y = 0; y < rows; y++) {
        // index of each row followed by a separator
        fprintf(stderr, "%2zu|", y);

        // data of each row
        for (size_t x = 0; x < cols; x++) {
            fprintf(stderr, "%3c", grid[y][x]);
        }

        fprintf(stderr, "\n");
    }
}

bool walkable(const point_t *p) {
    // TODO: check collisions of my own trolls, predict the movements
    return (grid[p->y][p->x] == '.'); 
}

bool point_equal(const point_t *p, const point_t *q) {
    return (p->x == q->x && p->y == q->y);
}
