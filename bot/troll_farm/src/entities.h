#ifndef ENTITIES_H
#define ENTITIES_H

#include <stddef.h>
#include <stdbool.h>
#include "game.h"

typedef enum type_e {
    PLUM,
    LEMON,
    APPLE,
    BANANA
} type_t;

typedef struct inventory_s {
    int plums;
    int lemons;
    int apples;
    int bananas;
    int iron;
    int wood;
} inventory_t;

typedef struct tree_s {
    type_t type;
    point_t p;
    int size;
    int health;
    int fruits;
    int cooldown;
} tree_t;

typedef struct troll_s {
    int id;
    int player; // 0 = my, 1 = opp
    point_t p;
    int movement_speed;
    int carry_capacity;
    int harvest_power;
    int chop_power;
    int carry_plum;
    int carry_lemon;
    int carry_apple;
    int carry_banana;
    int carry_iron;
    int carry_wood;
} troll_t;

extern inventory_t me;
extern inventory_t opp;

extern size_t tree_count;
extern tree_t trees[MAX_WIDTH * MAX_HEIGHT];

extern size_t my_troll_count;
extern troll_t my_trolls[MAX_TROLLS];

extern size_t opp_troll_count;
extern troll_t opp_trolls[MAX_TROLLS];

extern point_t my_shack;

void update_inventory(bool _me);
void update_trees(void);
void update_trolls(void);

void print_inventories(void);
void print_trees(void);
void print_trolls(void);

#endif /* ENTITIES_H */
