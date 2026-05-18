#ifndef OUTPUT_H
#define OUTPUT_H

#include "game.h"

extern const char *ACTONS[10];

void action_move(const int id, const point_t *p);
void action_harvest(const int id);
void action_plant(const int id, const char *type);
void action_chop(const int id);
void action_pick(const int id, const char *type);
void action_drop(const int id);
void action_train(const int a, const int b, const int c, const int d);
void action_mine(const int id);
void action_wait(void);
void action_msg(const char *text);

#endif /* OUTPUT_H */
