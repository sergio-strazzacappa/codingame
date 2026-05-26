#ifndef STRATEGY_H
#define STRATEGY_H

#include <stddef.h>
#include "entities.h"

void greedy(void);

double distance(const Point p, const Point q);

typedef struct {
    Point ash;

    size_t humans_count;
    Human humans[MAX_HUMANS];

    size_t zombies_count;
    Zombie zombies[MAX_ZOMBIES];
} State;

typedef struct {
    State s;
    int first_child;
    int sibling;
} Node;

extern Node root;

void create_node(void);

#endif /* STRATEGY_H */
