#ifndef ENTITIES_H
#define ENTITIES_H

#include "game.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int id;
    Point pos;
} Human;

typedef struct {
    int id;
    Point pos;
    Point next_pos;
} Zombie;

extern const int FIB[];

extern Point ash;

extern size_t human_count;
extern Human humans[MAX_HUMANS];

extern size_t zombie_count;
extern Zombie zombies[MAX_ZOMBIES];

void read_input(void);

Point move(const Point from, const Point to, const int limit);
Point move_zombie(const Point zombie, const Point humans[], const size_t hc,
                  const Point ash);
size_t kill_zombies(const Point ash);
size_t kill_humans(void);
double distance(const Point p, const Point q);

// debug
void print_ash(void);
void print_humans(const Human humans[], const size_t hc);
void print_zombies(const Zombie zombies[], const size_t zc);

#endif /* ENTITIES_H */
