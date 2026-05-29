#ifndef STRATEGY_H
#define STRATEGY_H

#include <stddef.h>
#include "entities.h"

typedef struct {
    Point ash;

    size_t human_count;
    Human humans[MAX_HUMANS];

    size_t zombie_count;
    Zombie zombies[MAX_ZOMBIES];

    double eval;
} State;

typedef struct {
    State s;
    Point action; // MOVE to ... to reach this state
    int parent;
} Node;

extern const int FIB[];
extern size_t pool_count;
extern Node pool[POOL_SIZE];

void greedy(void);
void beam_search(void);

void init_tree(State root);
State create_state(const Point ash,
    const size_t human_count, const Human humans[],
    const size_t zombie_count, const Zombie zombies[],
    const double parent_eval);
State next_state(const State *s, const Point target);
Point move(const Point from, const Point to, const int limit);
double evaluate(const State *s, const double parent_eval);
State clone_state(const State *s);

// utilities
int n_live_humans(const State *s);
int n_live_zombies(const State *s);
double distance(const Point p, const Point q);
int cmp(const void *a, const void *b);

// debug
void print_tree(void);
void print_node(const Node *n);
void print_state(const State *s);
void print_tree_structure(void);

#endif /* STRATEGY_H */
