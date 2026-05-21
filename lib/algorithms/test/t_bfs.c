#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "../include/bfs.h"

int main(void) {
    point_t start = {5, 5};
    point_t end = {5, 6};
    point_t *next = (point_t *)malloc(sizeof(point_t));

    size_t distance = bfs_v1(&start, &end, next);

    if (next != NULL)
        printf("Distance is %zu. The next cell is (%d, %d)\n",
            distance, next->x, next->y);
    else
        printf("Can't reach (%d, %d)\n", end.x, end.y);

    free(next);

    return EXIT_SUCCESS;
}
