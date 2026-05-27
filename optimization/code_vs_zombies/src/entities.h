#ifndef ENTITIES_H
#define ENTITIES_H

#include <stddef.h>
#include <stdbool.h>
#include "game.h"

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int id;
    Point pos;
    bool dead;
} Human;

typedef struct {
    int id;
    Point pos;
    Point next;
    bool dead;
} Zombie;

extern Point ash;

extern size_t human_count;
extern Human humans[MAX_HUMANS];

extern size_t zombie_count;
extern Zombie zombies[MAX_ZOMBIES];

void read_input(void);

void print_ash(void);
void print_humans(void);
void print_zombies(void);

#endif /* ENTITIES_H */
