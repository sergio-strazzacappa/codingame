#ifndef BFS_H
#define BFS_H

#include <stddef.h>
#include <stdbool.h>

#define ROWS 20
#define COLS 20

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

/*
 * BFS search (pathfinding) from start to end.
 * Stores in next the next point the optiomal path
 * Returns the length of the shortest path.
 */
size_t bfs_v1(const point_t *start, const point_t *end, point_t *next);

void print_matrix(const bool m[ROWS][COLS], const size_t rows, const size_t cols);
void print_array(const node_t a[ROWS * COLS], const size_t size);

#endif /* BFS_H */
