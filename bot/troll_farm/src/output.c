#include <stdio.h>
#include "output.h"

const char *ACTIONS[8] = {
    "MOVE",
    "HARVEST",
    "PLANT",
    "PICK",
    "DROP",
    "TRAIN",
    "WAIT",
    "MSG"
};

void action_move(const int id, const point_t p) {
    printf("%s %d %d %d;", ACTIONS[0], id, p.x, p.y);
}

void action_harvest(const int id) {
    printf("%s %d;", ACTIONS[1], id);
}

void action_plant(const int id, const char *type) {
    printf("%s %d %s;", ACTIONS[2], id, type);
}

void action_pick(const int id, const char *type) {
    printf("%s %d %s;", ACTIONS[3], id, type);
}

void action_drop(const int id) {
    printf("%s %d;", ACTIONS[4], id);
}

void action_train(const int a, const int b, const int c, const int d) {
    /*
     * a: moveSpeed
     * b: carryCapacity
     * c: harvestPower
     * d: chopPower
     */

    printf("%s %d %d %d %d;", ACTIONS[5], a, b, c, d);
}

void action_wait(void) {
    printf("%s;", ACTIONS[6]);
}

void action_msg(const char *text) {
    printf("%s %s;", ACTIONS[7], text);
}
