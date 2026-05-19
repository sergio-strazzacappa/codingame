#ifndef STRATEGY_H
#define STRATEGY_H

#include <stddef.h>
#include "map.h"
#include "entities.h"

typedef struct node_s {
    point_t current;
    int parent_idx;
    size_t dist;
} node_t;

size_t pathfinding(const point_t *start, const point_t *end, point_t *next);
bool is_tree(const point_t *p);
bool is_troll_full(const troll_t *t);
void chopper(const troll_t *t);
void train_troll(void);

#endif /* STRATRGY_H*/
