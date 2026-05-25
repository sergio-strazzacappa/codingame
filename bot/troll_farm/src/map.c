#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
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
bool near_water[MAX_HEIGHT][MAX_WIDTH];
int distances_from_shack[MAX_HEIGHT][MAX_WIDTH];
point_t next_turn[MAX_TROLLS];

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

void precompute_near_water(void) {
    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            near_water[y][x] = false;

            for (size_t i = 0; i < 4; i++) {
                point_t p = {x + DIRS[i][0], y + DIRS[i][1]};

                if (p.x < 0)
                    continue;
                if (p.x >= (int)cols)
                    continue;
                if (p.y < 0)
                    continue;
                if (p.y >= (int)rows)
                    continue;

                if (grid[p.y][p.x] == '~') {
                    near_water[y][x] = true;
                    break;
                }
            }
        }
    }
}

void precompute_distances_from_shack(void) {
    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            point_t p = {x, y};
            distances_from_shack[y][x] = manhattan_distance(&p, &my_shack);
        }
    }
}

/*
 * TODO: Take in consideration the speed of my trolls
 */
int pathfinding(const point_t *start, const point_t *end, point_t *next) {
    // start and end are the same cell
    if (point_equal(start, end)) {
        if (next != NULL)
            *next = *end;
        return 0;
    }

    bool visited[MAX_HEIGHT][MAX_WIDTH] = {false};

    node_t queue[MAX_HEIGHT * MAX_WIDTH];
    size_t head = 0;
    size_t tail = 0;

    // queue the starting point
    queue[tail++] = (node_t){*start, -1, 0};
    visited[start->y][start->x] = true;

    int target_idx = -1;

    while (head < tail) {
        int current_idx = (int)head;
        node_t n = queue[head++];

        if (point_equal(&(n.current), end)) {
            target_idx = current_idx;
            break;
        }

        for (size_t i = 0; i < 4; i++) {
            point_t p = {n.current.x + DIRS[i][0], n.current.y + DIRS[i][1]};

            if (p.x < 0)
                continue;
            if (p.x >= (int)cols)
                continue;
            if (p.y < 0)
                continue;
            if (p.y >= (int)rows)
                continue;
            if (!walkable(&p, end, next_turn))
                continue;
            if (visited[p.y][p.x])
                continue;

            assert(tail < rows * cols);

            // add the nodes to the frontier
            visited[p.y][p.x] = true;
            queue[tail++] = (node_t){p, current_idx, n.distance + 1};
        }
    }

    if (target_idx != -1) {
        // end reached
        int curr = target_idx;

        if (next != NULL) {
            // build the path
            point_t tmp;
            while (queue[curr].parent_idx != -1) {
                tmp = queue[curr].current;
                curr = queue[curr].parent_idx;
            }

            *next = tmp;
        }

        return queue[target_idx].distance;
    }

    // unreachable
    return -1;
}

// UTILITIES -------------------------------------------------------------------

bool point_equal(const point_t *p, const point_t *q) {
    return (p->x == q->x && p->y == q->y);
}

int manhattan_distance(const point_t *p, const point_t *q) {
    return abs(p->x - q->x) + abs(p->y - q->y);
}

bool is_tree(const point_t *p) {
    for (size_t i = 0; i < tree_count; i++) {
        tree_t t = trees[i];

        if (point_equal(p, &t.p))
            return true;
    }

    return false;
}

/*
 * return if point p is walkable
 *
 * @param p: point in the grid to test if it is walkable
 * @param end: end point of the journey, include my shack if it is the end
 * @param next_turn: array of points of my next turn trolls to avoid collisions
 * @return true if p is walkable, otherwise false
 */
bool walkable(const point_t *p, const point_t *end, const point_t *next_turn) {
    if (point_equal(p, end) && grid[p->y][p->x] == '0')
        return true;

    if (point_equal(p, end) && grid[p->y][p->x] == '+')
        return true;

    for (size_t i = 0; i < my_troll_count; i++) {
        if (point_equal(p, &next_turn[i]))
            return false;
    }

    return grid[p->y][p->x] == '.';
}

// DEBUG -----------------------------------------------------------------------

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

void near_water_print(void) {
    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            fprintf(stderr, "%2d", near_water[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

void distances_from_shack_print(void) {
    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            fprintf(stderr, "%2d", distances_from_shack[y][x]);
        }
        fprintf(stderr, "\n");
    }
}
