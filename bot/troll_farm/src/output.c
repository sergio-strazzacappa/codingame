#include <stdio.h>
#include "output.h"

const char *ACTIONS[10] = {
    "MOVE",
    "HARVEST",
    "PLANT",
    "CHOP",
    "PICK",
    "DROP",
    "TRAIN",
    "MINE",
    "WAIT",
    "MSG"
};

void action_move(const int id, const point_t *p) {
    printf("%s %d %d %d;", ACTIONS[0], id, p->x, p->y);
}

void action_harvest(const int id) {
    printf("%s %d;", ACTIONS[1], id);
}

void action_plant(const int id, const char *type) {
    printf("%s %d %s;", ACTIONS[2], id, type);
}

void action_chop(const int id) {
    printf("%s %d;", ACTIONS[3], id);
}

void action_pick(const int id, const char *type) {
    printf("%s %d %s;", ACTIONS[4], id, type);
}

void action_drop(const int id) {
    printf("%s %d;", ACTIONS[5], id);
}

void action_train(const int a, const int b, const int c, const int d) {
    /*
     * a: moveSpeed
     * b: carryCapacity
     * c: harvestPower
     * d: chopPower
     */

    printf("%s %d %d %d %d;", ACTIONS[6], a, b, c, d);
}

void action_mine(const int id) {
    printf("%s %d;", ACTIONS[7], id);
}

void action_wait(void) {
    printf("%s;", ACTIONS[8]);
}

void action_msg(const char *text) {
    printf("%s %s;", ACTIONS[9], text);
}
