#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <stdbool.h>
#include "entities.h"
#include "greedy.h"

void run(void) {

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
        bool found = true;

        double d = distance(ash, humans[i].pos) - 2000; // distance - radius
        int ash_turns = d <= 1000 ? 1 : d / 1000;

        if (d < closest_human_distance) {
            // save the closest human from Ash
            closest_human_distance = d;
            closest_human = humans[i].pos;
        }

        fprintf(stderr, "Ash reaches human (%d, %d) in %d turns\n",
            humans[i].pos.x, humans[i].pos.y, ash_turns);

        for (size_t j = 0; j < zombie_count; j++) {
            d = distance(humans[i].pos, zombies[j].next);
            int turns_left = d <= 400 ? 1 : d / 400;

            if (turns_left < ash_turns) {
                // if the human can't be saved go to the next human, ignores
                // the next zombies
                fprintf(stderr, "Human at (%d, %d) is dead\n",
                    humans[i].pos.x, humans[i].pos.y);

                found = false;
                break;
            }

            if (turns_left < min_zombie) {
                // save the closest reachable zombie frim the current human
                min_zombie = turns_left;
                target_zombie = zombies[j].pos;
            }
        }

        if (found && min_zombie < min_human) {
            // the human can be saved
            target = target_zombie;
            min_human = min_zombie;
        }

        fprintf(stderr, "Human (%d, %d) dies in %d turns - found %d\n",
            humans[i].pos.x, humans[i].pos.y, min_zombie, found);
    }

    if (target.x != -1) {
        // no human can be saved. Go to the closest human
        fprintf(stderr, "[INFO] Go to the zombie\n");
        printf("%d %d\n", target.x, target.y);
    } else {
        fprintf(stderr, "[INFO] Go to the human\n");
        printf("%d %d\n", closest_human.x, closest_human.y);
    }
}

double distance(const Point p, const Point q) {
    return hypot(p.x - q.x, p.y - q.y);
}
