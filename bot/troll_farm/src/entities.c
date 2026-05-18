#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "entities.h"
#include "game.h"

const char* TYPE_NAMES[] = {
    "PLUM",
    "LEMON",
    "APPLE",
    "BANANA"
};

inventory_t me;
inventory_t opp;

size_t tree_count;
tree_t trees[MAX_WIDTH * MAX_HEIGHT];

size_t my_troll_count;
troll_t my_trolls[MAX_TROLLS];

size_t opp_troll_count;
troll_t opp_trolls[MAX_TROLLS];

point_t my_shack;

void update_inventory(bool _me) {
    inventory_t *inv = _me ? &me : &opp;

    scanf("%d%d%d%d%d%d",
        &inv->plums, &inv->lemons, &inv->apples, &inv->bananas,
        &inv->iron, &inv->wood);
}

void update_trees(void) {
    scanf("%zu", &tree_count);

    for (size_t i = 0; i < tree_count; i++) {
        char type[16];

        scanf("%15s%d%d%d%d%d%d", type, &trees[i].p.x, &trees[i].p.y,
            &trees[i].size, &trees[i].health, &trees[i].fruits,
            &trees[i].cooldown);

        if (strcmp(type, "PLUM") == 0)      trees[i].type = PLUM;
        if (strcmp(type, "LEMON") == 0)     trees[i].type = LEMON;
        if (strcmp(type, "APPLE") == 0)     trees[i].type = APPLE;
        if (strcmp(type, "BANANA") == 0)    trees[i].type = BANANA;

        trees[i].claimed = false;

    }
}

void update_trolls(void) {
    size_t total_trolls;
    scanf("%zu", &total_trolls);

    my_troll_count = 0;
    opp_troll_count = 0;

    for (size_t i = 0; i < total_trolls; i++) {
        troll_t t;
        scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &t.id, &t.player, &t.p.x, &t.p.y,
            &t.movement_speed, &t.carry_capacity, &t.harvest_power,
            &t.chop_power, &t.carry_plum, &t.carry_lemon, &t.carry_apple,
            &t.carry_banana, &t.carry_iron, &t.carry_wood);

        if (t.player == 0)
            my_trolls[my_troll_count++] = t;
        else
            opp_trolls[opp_troll_count++] = t;
    }
}

void print_inventories(void) {
    fprintf(stderr, "[DEBUG] My inventory {%d, %d, %d, %d, %d, %d}\n", me.plums,
        me.lemons, me.apples, me.bananas, me.iron, me.wood);

    fprintf(stderr, "[DEBUG] Opp inventory {%d, %d, %d, %d, %d, %d}\n",
        opp.plums, opp.lemons, opp.apples, opp.bananas, opp.iron, opp.wood);
}

void print_trees(void) {
    fprintf(stderr, "[DEBUG] Trees:\n");

    for (size_t i = 0; i < tree_count; i++) {
        fprintf(stderr, "[DEBUG] \t(%s, %d, %d, %d, %d, %d, %d, %d)\n",
            TYPE_NAMES[trees[i].type], trees[i].p.x, trees[i].p.y, trees[i].size,
            trees[i].health, trees[i].fruits, trees[i].cooldown, trees[i].claimed);
    }
}

void print_trolls(void) {
    fprintf(stderr, "[DEBUG] My trolls:\n");

    for (size_t i = 0; i < my_troll_count; i++) {
        troll_t t = my_trolls[i];
        fprintf(stderr,
            "[DEBUG] \t(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)\n",
            t.id, t.player, t.p.x, t.p.y, t.movement_speed, t.carry_capacity,
            t.harvest_power, t.chop_power, t.carry_plum, t.carry_lemon,
            t.carry_apple, t.carry_banana, t.carry_iron, t.carry_wood);
    }

    fprintf(stderr, "[DEBUG] Opponent trolls:\n");

    for (size_t i = 0; i < opp_troll_count; i++) {
        troll_t t = opp_trolls[i];
        fprintf(stderr,
            "[DEBUG] \t(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)\n",
            t.id, t.player, t.p.x, t.p.y, t.movement_speed, t.carry_capacity,
            t.harvest_power, t.chop_power, t.carry_plum, t.carry_lemon,
            t.carry_apple, t.carry_banana, t.carry_iron, t.carry_wood);
    }
}
