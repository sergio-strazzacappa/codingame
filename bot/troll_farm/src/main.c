#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "map.h"
#include "entities.h"
#include "strategy.h"
#include "output.h"

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    map_init();

    while (true) {
        clock_t start, end;

        if (DEBUG)
            start = clock();

        update_inventory(true);
        update_inventory(false);
        update_trees();
        update_trolls();

        compute_tasks();
        print_tasks();

        for (size_t i = 0; i < my_troll_count; i++) {
//            chopper(&my_trolls[i]);
        }

        train_troll();

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
