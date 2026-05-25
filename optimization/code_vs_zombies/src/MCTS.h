#ifndef MCTS_H
#define MCTS_H

#include <stddef.h>
#include "entities.h"

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

#endif /* MCTS_H */
