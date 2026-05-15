#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "map.h"
#include "entities.h"
#include "strategy.h"

int turn = 0;

int main(void) {
    map_init();
   //map_print();

    status_t status[32] = {TO_TREE};
    while (true) {
        turn++;
        update_inventory(true);
        update_inventory(false);
        update_trees();
        update_trolls();

        wood1(status);
        train_troll(turn);

        printf("\n");

        //print_inventories();
        //print_trees();
        //print_trolls();
    }

    return EXIT_SUCCESS;
}
