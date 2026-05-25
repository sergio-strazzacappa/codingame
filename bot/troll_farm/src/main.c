#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "map.h"
#include "entities.h"
#include "strategy.h"
#include "output.h"

size_t turn;

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    map_init();
    precompute_near_water();
    precompute_distances_from_shack();

    turn = 0;

    while (true) {
        clock_t start, end;

        if (DEBUG)
            start = clock();

        turn++;

        update_inventory(true);
        update_inventory(false);
        update_trees();
        update_trolls();

        // set the array of next positions to the current positions
        for (size_t i = 0; i < my_troll_count; i++)
            next_turn[i] = (point_t){my_trolls[i].p.x, my_trolls[i].p.y};

        plant(turn);
        send();
        compute_tasks(turn);
        train_troll();
        print_tasks();

        if (DEBUG) {
            end = clock();
            double ms = (double)(end - start) /  CLOCKS_PER_SEC * 1000.0;
            char msg[512];
            sprintf(msg, "%.2fms", ms);

            action_msg(msg);
        }

        printf("\n");
    }

    return EXIT_SUCCESS;
}
