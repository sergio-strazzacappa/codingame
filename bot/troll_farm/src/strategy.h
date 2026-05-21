#ifndef STRATEGY_H
#define STRATEGY_H

#include <stddef.h>
#include "map.h"
#include "entities.h"

typedef struct node_s {
    point_t current;
    int parent_idx;
    size_t distance;
} node_t;

typedef struct task_s {
    int troll_id;
    point_t pos;
    int cost;
} task_t;

extern task_t tasks[MAX_TASKS];
extern size_t task_count;

int cmp(const void *a, const void *b);
point_t *get_troll_pos(const int id);
void compute_tasks(void);
int pathfinding(const point_t *start, const point_t *end, point_t *next);
bool is_tree(const point_t *p);
bool is_troll_full(const troll_t *t);
void chopper(const troll_t *t);
void train_troll(void);

// debug functions
void print_tasks(void);

#endif /* STRATRGY_H*/
