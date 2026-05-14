#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "map.h"
#include "entities.h"
#include "strategy.h"

int main(void) {
    map_init();
   //map_print();

    status_t status = TO_TREE;
    while (true) {
        update_inventory(true);
        update_inventory(false);
        update_trees();
        update_trolls();

        wood2(&status);

        //print_inventories();
        //print_trees();
        //print_trolls();
    }

    return EXIT_SUCCESS;
}
