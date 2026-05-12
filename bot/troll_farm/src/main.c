#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "map.h"
#include "entities.h"

int main(void) {
    map_init();
    map_print();

    while (true) {
        update_inventory(true);        
        update_inventory(false);        
        update_trees();
        update_trolls();

        print_inventories();
        print_trees();
        print_trolls();
    }

    return EXIT_SUCCESS;
}
