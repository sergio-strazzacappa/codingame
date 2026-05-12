#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include "game.h"

extern size_t rows;
extern size_t cols;
extern char grid[MAX_HEIGHT][MAX_WIDTH];

void map_init();
void map_print();

#endif /* MAP_H */
