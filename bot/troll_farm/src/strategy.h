#ifndef STRATEGY_H
#define STRATEGY_H

#include "game.h"
#include "entities.h"

int distance(const point_t *p, const point_t *q);
bool is_tree(const point_t *p);
bool is_troll_full(const troll_t *t);
size_t my_troll_count(void);
bool enough_plums(void);
bool enough_lemons(void);
bool enough_apples(void);
void train_troll(const int turn);
void wood1(status_t status[]);

#endif /* STRATRGY_H*/
