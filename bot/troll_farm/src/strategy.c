#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "strategy.h"
#include "entities.h"
#include "game.h"
#include "output.h"

// return the manhattan distance beteween p and q
int distance(const point_t *p, const point_t *q) {
   return abs(q->x - p->x) + abs(q->y - p->y);
}

// return true if point p is a tree and fruits > 0
bool is_tree(const point_t *p) {
   for (size_t i = 0; i < tree_count; i++) {
      tree_t t = trees[i];

      if (t.x == p->x && t.y == p->y && t.fruits > 0)
         return true;
   }

   return false;
}

// return true if troll t capacity is full
bool is_troll_full(const troll_t *t) {
   int carry = t->carry_plum + t->carry_lemon + t->carry_apple + t->carry_banana;

   return carry == t->carry_capacity;
}

size_t my_troll_count(void) {
   size_t count = 0;

   for (size_t i = 0; i < troll_count; i++) {
      if (trolls[i].player == 0)
         count++;
   }

   return count;
}

bool enough_plums(void) {
   return me.plums >= my_troll_count() + OPTIMAL_TRAIN * OPTIMAL_TRAIN;
}

bool enough_lemons(void) {
   return me.lemons >= my_troll_count() + OPTIMAL_TRAIN * OPTIMAL_TRAIN;
}

bool enough_apples(void) {
   return me.apples >= my_troll_count() + OPTIMAL_TRAIN * OPTIMAL_TRAIN;
}

void train_troll(const int turn) {
   if (turn > 50)
      return;
   int a = enough_plums() ? 1 : 0;
   int b = enough_lemons() ? 1 : 0;
   int c = enough_apples() ? 1 : 0;
   int d = 0;

   fprintf(stderr, "%d %d %d %d\n", a, b, c, d);

   if (a == 0 || b == 0 || c == 0)
      return;

   action_train(a, b, c, d);
}

void wood1(status_t status[]) {
   int troll_index = -1;
   for (size_t i = 0; i < troll_count; i++) {
      troll_t t = trolls[i];

      if (t.player == 1)
         continue;

      troll_index++;
      point_t p = {t.x, t.y};
      int d = distance(&p, &my_shack);

      fprintf(stderr, "(%d, %d) -> (%d, %d) = %d\n", p.x, p.y, my_shack.x, my_shack.y, d);

      for (size_t j = 0; j < 10; j++) {
         fprintf(stderr, "%d  ", status[j]);
      }

      fprintf(stderr, "index:%d\n", troll_index);

      if (status[troll_index] == RETURN && d == 1)
         status[troll_index] = DROP;
      else if (is_troll_full(&t))
         status[troll_index] = RETURN;
      else if (is_tree(&p))
         status[troll_index] = HARVEST;
      else
         status[troll_index] = TO_TREE;

      if (status[troll_index] == TO_TREE) {
         int min = INT_MAX;
         int index = 0;

         for (size_t j = 0; j < tree_count; j++) {
            if (trees[j].fruits == 0)
               continue;
            if (trees[j].fruits == 1 && my_troll_count() == 2)
               continue;

            point_t q = (point_t){trees[j].x, trees[j].y};
            d = distance(&p, &q);

            if (d < min) {
               min = d;
               index = j;
            }
         }

         point_t target = {trees[index].x, trees[index].y};
         action_move(t.id, target);

      } else if (status[troll_index] == HARVEST) {
         action_harvest(t.id);
      } else if (status[troll_index] == RETURN) {
         action_move(t.id, my_shack);
      } else if (status[troll_index] == DROP) {
         action_drop(t.id);
      }
   }
}
