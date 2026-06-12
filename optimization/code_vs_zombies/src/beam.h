#ifndef BEAM_H
#define BEAM_H

#include <stddef.h>
#include <stdbool.h>
#include "entities.h"

#define POOL_SIZE       2000   // 1 + (BEAM_MAX_STATES * BEAM_K)
#define MAX_STATES      7000    // BEAM_K * BRANCHING_FACTOR
#define BEAM_K          40
#define BEAM_MAX_DEPTH  50
#define TIME_LIMIT      95      // ms

typedef struct {
    Point ash;

    size_t human_count;
    Human humans[MAX_HUMANS];

    size_t zombie_count;
    Zombie zombies[MAX_ZOMBIES];

    int score;      // score of the game from the root
    double eval;    // evaluation (h) of this state
} State;

typedef struct {
    int id;
    State s;
    Point action;   // MOVE to ... to reach this state
    int parent;
    bool is_leaf;
} Node;

extern const int FIB[];
extern size_t pool_count;
extern Node pool[POOL_SIZE];

void run(void);

// tree
State create_state(const Point ash,
    const size_t human_count, const Human humans[],
    const size_t zombie_count, const Zombie zombies[],
    const int parent_score);
void init_tree(const State *root);
State clone_state(const State *s);
bool node_equal(const Node *n1, const Node *n2);

// game
State next_state(const State *s, const Point target, const size_t depth);
Point move(const Point from, const Point to, const int limit);
Point move_zombie(const Point from, const State *s);

// score
int score(const State *s, const int parent_score, const size_t kills);
double h(const State *s);

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

#endif /* BEAM_H */
