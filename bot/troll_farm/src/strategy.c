#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "strategy.h"
#include "entities.h"
#include "game.h"

int distance(const point_t p, const point_t q) {
   return abs(q.x - p.x) + abs(q.y - p.y);
}

bool is_tree(point_t p) {
   for (size_t i = 0; i < tree_count; i++) {
      tree_t t = trees[i];

      if (t.x == p.x && t.y == p.y)
         return true;
   }

   return false;
}

bool is_troll_full(troll_t t) {
   int carry = t.carry_plum + t.carry_lemon + t.carry_apple + t.carry_banana;

   return carry == t.carry_capacity;
}

void wood2(status_t *status) {
   for (size_t i = 0; i < troll_count; i++) {
      troll_t t = trolls[i];

      if (t.player == 1)
         continue;

      point_t p = {t.x, t.y};
      int d = distance(p, my_shack);

      fprintf(stderr, "(%d, %d) -> (%d, %d) = %d\n", p.x, p.y, my_shack.x, my_shack.y, d);

      if (*status == RETURN && d == 1)
         *status = DROP;
      else if (is_troll_full(t))
         *status = RETURN;
      else if (is_tree(p))
         *status = HARVEST;
      else
         *status = TO_TREE;

      char action[32], msg[32];

      if (*status == TO_TREE) {
         int min = INT_MAX;
         int index = 0;

         for (size_t j = 0; j < tree_count; j++) {
            if (trees[j].fruits == 0)
               continue;

            point_t q = (point_t){trees[j].x, trees[j].y};
            d = distance(p, q);

            if (d < min) {
               min = d;
               index = j;
            }
         }

         sprintf(action, "MOVE %d %d %d", t.id, trees[index].x, trees[index].y);

      } else if (*status == HARVEST) {
         sprintf(action, "HARVEST %d", t.id);
      } else if (*status == RETURN) {
         sprintf(action, "MOVE %d %d %d", t.id, my_shack.x, my_shack.y);
      } else if (*status == DROP) {
         sprintf(action, "DROP %d", t.id);
      }

      sprintf(msg, "MSG status:%d", *status);

      printf("%s;%s\n", action, msg);
   }
}
