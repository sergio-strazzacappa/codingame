#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdbool.h>
#include "game.h"

typedef struct point_s {
    int x;
    int y;
} point_t;

extern const int DIRS[4][2];
extern size_t rows;
extern size_t cols;
extern char grid[MAX_HEIGHT][MAX_WIDTH];

void map_init(void);
void map_print(void);
bool walkable(const point_t *p);
bool point_equal(const point_t *p, const point_t *q);

#endif /* MAP_H */
