#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "strategy.h"
#include "entities.h"
#include "game.h"
#include "output.h"

// return the manhattan distance beteween p and q
size_t distance(const point_t *p, const point_t *q) {
   return abs(q->x - p->x) + abs(q->y - p->y);
}

// return true if point p is a tree and fruits > 0
bool is_tree(const point_t *p) {
   for (size_t i = 0; i < tree_count; i++) {
      tree_t t = trees[i];

      if (t.p.x == p->x && t.p.y == p->y && t.fruits > 0)
         return true;
   }

   return false;
}

// return true if troll t capacity is full
bool is_troll_full(const troll_t *t) {
   int carry =
      t->carry_plum + t->carry_lemon + t->carry_apple + t->carry_banana +
      t->carry_iron + t->carry_wood;

   return carry >= t->carry_capacity;
}

void chopper(const troll_t *t) {
   if (!is_troll_full(t)) {
      size_t closest = INT_MAX;
      size_t target = 0;

      for (size_t i = 0; i < tree_count; i++) {
         if (trees[i].claimed)
            continue;

         size_t d = distance(&(t->p), &(trees[i].p));

         if (d < closest) {
            closest = d;
            target = i;
         }
      }

      if (closest == 0) {
         trees[target].claimed = true;
         action_chop(t->id);
         return;
      }

      trees[target].claimed = true;
      action_move(t->id, &(trees[target].p));
      return;
   }

   size_t d = distance(&(t->p), &my_shack);

   if (d == 1) {
      action_drop(t->id);
      return;
   }

   action_move(t->id, &my_shack);
}

void train_troll(void) {
   /*
    * basic train function: train the min chopper
    *
    * movement_speed 1 = my_troll_count + 1 plum
    * carry_capacity 1 = my_troll_count + 1 lemon
    * harvest_power 0 = my_troll_count apple
    * chop_power 1 = my_troll_count + 1 iron
    */


   if ((size_t)me.plums < my_troll_count + 1)
      return;

   if ((size_t)me.lemons < my_troll_count + 1)
      return;

   if ((size_t)me.apples < my_troll_count)
      return;

   if ((size_t)me.iron < my_troll_count + 1)
      return;

   action_train(1, 1, 0, 1);
}
