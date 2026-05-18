#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "map.h"
#include "entities.h"
#include "strategy.h"

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    map_init();

    while (true) {
        update_inventory(true);
        update_inventory(false);
        update_trees();
        update_trolls();

        for (size_t i = 0; i < my_troll_count; i++) {
            chopper(&my_trolls[i]);
        }

        train_troll();

        printf("\n");
    }

    return EXIT_SUCCESS;
}
