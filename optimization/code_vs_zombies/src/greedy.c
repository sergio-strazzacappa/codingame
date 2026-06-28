#include "greedy.h"
#include "entities.h"
#include "game.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

Point run(void) {
    /*
     * Check for every human the distance to the closest zombie. The greedy
     * algorithm moves Ash towards the zombie that can kill a human sooner.
     * But if the human can't be saved (ash is too far) that human is discarded
     */

    Point target = {-1, -1};
    Point closest_human = {0, 0};
    int closest_human_distance = INF;
    int min_human = INF;

    for (size_t i = 0; i < human_count; i++) {
        int min_zombie = INF;
        Point target_zombie = {0, 0};
        bool is_safe = true;

        double d = distance(ash, humans[i].pos);

        if (d < closest_human_distance) {
            // save the closest human from Ash
            closest_human_distance = d;
            closest_human = humans[i].pos;
        }

        for (size_t j = 0; j < zombie_count; j++) {
            double d_h_z = distance(humans[i].pos, zombies[j].pos);
            int turns_zombie = ceil(d_h_z / ZOMBIE_SPEED);

            double d_a_z = distance(ash, zombies[j].pos) - ASH_RADIUS;
            int turns_ash = ceil(d_a_z / ASH_SPEED);

            if (turns_ash < 0)
                turns_ash = 0;

            if (turns_zombie < turns_ash) {
                // if the human can't be saved go to the next human, ignores
                // the next zombies
                fprintf(stderr, "Human at (%d, %d) is dead in %d turns\n",
                        humans[i].pos.x, humans[i].pos.y, turns_zombie);
                is_safe = false;
                break;
            }

            if (turns_zombie < min_zombie) {
                // save the closest reachable zombie from the current human
                min_zombie = turns_zombie;
                target_zombie = zombies[j].next_pos;
            }
        }

        if (is_safe && min_zombie < min_human) {
            // the human can be saved
            target = target_zombie;
            min_human = min_zombie;
        }

        if (is_safe)
            fprintf(stderr, "Human (%d, %d) dies in %d turns\n",
                    humans[i].pos.x, humans[i].pos.y, min_zombie);
    }

    if (target.x != -1) {
        fprintf(stderr, "[INFO] Go to the zombie (%d, %d)\n", target.x,
                target.y);
        return target;
    } else {
        // no human can be saved. Go to the closest human
        fprintf(stderr, "[INFO] Go to the human\n");
        return closest_human;
    }
}
