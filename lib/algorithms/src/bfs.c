#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/bfs.h"

const int DIRS[4][2] = {
    { +0, -1 },
    { +1, +0 },
    { +0, +1 },
    { -1, +0 }
};

size_t bfs_v1(const point_t *start, const point_t *end, point_t *next) {
    if (start->x == end->x && start->y == end->y) {
        *next = *end;

        return 0;
    }

    bool visited[ROWS][COLS] = {false};
    node_t queue[ROWS * COLS];
    size_t head = 0;
    size_t tail = 0;
    
    // queue the starting point
    queue[tail++] = (node_t){*start, -1, 0};
    visited[start->y][start->x] = true;

    int target_idx = -1;

    while (head < tail) {
        int current_idx = (int)head;
        node_t n = queue[head++];

        if (n.current.x == end->x && n.current.y == end->y) {
            target_idx = current_idx;
            break;
        }

        for (size_t i = 0; i < 4; i++) {
            point_t p = {n.current.x + DIRS[i][0], n.current.y + DIRS[i][1]};

            // constraints
            if (p.x < 0)
                continue;
            if (p.x >= COLS)
                continue;
            if (p.y < 0)
                continue;
            if (p.y >= ROWS)
                continue;
            if (visited[p.y][p.x])
                continue;

            if (tail == ROWS * COLS) {
                fprintf(stderr, "[ERROR] queue is full\n");

                return EXIT_FAILURE;
            }

            // add the nodes to the frontier
            visited[p.y][p.x] = true;
            queue[tail++] = (node_t) {p, current_idx, n.distance + 1};
        }
    }

    print_matrix(visited, ROWS, COLS);
    print_array(queue, tail);

    if (target_idx != -1) {
        int curr = target_idx;

        while (queue[curr].parent_idx != 0) {
            curr = queue[curr].parent_idx;
        }

        if (next == NULL) {
            fprintf(stderr, "[ERROR] next is NULL\n");

            return EXIT_FAILURE;;
        }

        *next = queue[curr].current;

        return queue[target_idx].distance;
    }

    return 0;
}

void print_matrix(const bool m[ROWS][COLS], const size_t rows, const size_t cols) {
    printf("     ");

    for (size_t i = 0; i < cols; i++) {
        printf("%3zu", i);
    }

    printf("\n");
    printf("     ");

    for (size_t i = 0; i < cols; i++) {
        printf("---");
    }

    printf("\n");

    for (size_t y = 0; y < rows; y++) {
        printf("%3zu |", y);
        for (size_t x = 0; x < cols; x++) {
            printf("%3d", m[y][x]);
        }
        printf("\n");
    }
}

void print_array(const node_t a[ROWS * COLS], const size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%zu: current:(%d, %d) - parent:%d - distance:%zu\n",
            i, a[i].current.x, a[i].current.y, a[i].parent_idx, a[i].distance);
    }
}
