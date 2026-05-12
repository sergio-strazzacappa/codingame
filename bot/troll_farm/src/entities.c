#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "entities.h"

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
size_t troll_count;
troll_t trolls[MAX_WIDTH * MAX_HEIGHT];

void update_inventory(bool _me) {
    inventory_t *inv = _me ? &me : &opp;

    assert(inv != NULL);

    scanf("%d%d%d%d%d%d", &inv->plum, &inv->lemons, &inv->apples, &inv->bananas,
        &inv->iron, &inv->wood);
}

void update_trees(void) {
    scanf("%zu", &tree_count);

    for (size_t i = 0; i < tree_count; i++) {
        char type[16];

        scanf("%15s%d%d%d%d%d%d", type, &trees[i].x, &trees[i].y,
            &trees[i].size, &trees[i].health, &trees[i].fruits,
            &trees[i].cooldown);

        if (strcmp(type, "PLUM") == 0)      trees[i].type = PLUM;
        if (strcmp(type, "LEMON") == 0)     trees[i].type = LEMON;
        if (strcmp(type, "APPLE") == 0)     trees[i].type = APPLE;
        if (strcmp(type, "BANANA") == 0)    trees[i].type = BANANA;

    }
}

void update_trolls(void) {
    scanf("%zu", &troll_count);

    for (size_t i = 0; i < troll_count; i++) {
        scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
            &trolls[i].id, &trolls[i].player, &trolls[i].x, &trolls[i].y,
            &trolls[i].movement_speed, &trolls[i].carry_capacity,
            &trolls[i].harvest_power, &trolls[i].chop_power, &trolls[i].carry_plum,
            &trolls[i].carry_lemon, &trolls[i].carry_apple,
            &trolls[i].carry_banana, &trolls[i].carry_iron, &trolls[i].carry_wood);
    }
}

void print_inventories(void) {
    fprintf(stderr, "[DEBUG] My inventory {%d, %d, %d, %d, %d, %d}\n", me.plum,
        me.lemons, me.apples, me.bananas, me.iron, me.wood);

    fprintf(stderr, "[DEBUG] Opp inventory {%d, %d, %d, %d, %d, %d}\n",
        opp.plum, opp.lemons, opp.apples, opp.bananas, opp.iron, opp.wood);
}

void print_trees(void) {
    fprintf(stderr, "[DEBUG] Trees:");

    for (size_t i = 0; i < tree_count; i++) {
        fprintf(stderr, "[DEBUG] \t(%s, %d, %d, %d, %d, %d, %d)\n",
            TYPE_NAMES[trees[i].type], trees[i].x, trees[i].y, trees[i].size,
            trees[i].health, trees[i].fruits, trees[i].cooldown);
    }
}

void print_trolls(void) {
    fprintf(stderr, "[DEBUG] Trolls:");

    for (size_t i = 0; i < troll_count; i++) {
        fprintf(stderr,
            "[DEBUG] \t(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)\n",
            trolls[i].id, trolls[i].player, trolls[i].x, trolls[i].y,
            trolls[i].movement_speed, trolls[i].carry_capacity,
            trolls[i].harvest_power, trolls[i].chop_power, trolls[i].carry_plum,
            trolls[i].carry_lemon, trolls[i].carry_apple,
            trolls[i].carry_banana, trolls[i].carry_iron, trolls[i].carry_wood);
    }
}
