#ifndef STRATEGY_H
#define STRATEGY_H

#include "game.h"
#include "entities.h"

size_t distance(const point_t *p, const point_t *q);
bool is_tree(const point_t *p);
bool is_troll_full(const troll_t *t);
void chopper(const troll_t *t);
void train_troll(void);

#endif /* STRATRGY_H*/
