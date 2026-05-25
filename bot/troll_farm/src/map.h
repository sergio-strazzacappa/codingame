#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdbool.h>
#include "game.h"

typedef struct point_s {
    int x;
    int y;
} point_t;

typedef struct node_s {
    point_t current;
    int parent_idx;
    size_t distance;
} node_t;

extern const int DIRS[4][2];

extern size_t rows;
extern size_t cols;
extern char grid[MAX_HEIGHT][MAX_WIDTH];
extern bool near_water[MAX_HEIGHT][MAX_WIDTH];
extern int distances_from_shack[MAX_HEIGHT][MAX_WIDTH];
extern point_t next_turn[MAX_TROLLS];

void map_init(void);
void precompute_near_water(void);
void precompute_distances_from_shack(void);

int pathfinding(const point_t *start, const point_t *end, point_t *next);

// UTILIITES
bool point_equal(const point_t *p, const point_t *q);
int manhattan_distance(const point_t *p, const point_t *q);
bool is_tree(const point_t *p);
bool walkable(const point_t *p, const point_t *end, const point_t *next_turn);

// DEBUG
void map_print(void);
void near_water_print(void);
void distances_from_shack_print(void);

#endif /* MAP_H */
