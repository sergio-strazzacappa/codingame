#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "entities.h"
#include "game.h"
#include "greedy.h" // change to the algorithm used

int main(void) {
    while (true) {
        read_input();

        print_ash();
        print_humans(humans);
        print_zombies(zombies);

        run();

        if (DEBUG)
            break; // run only one turn
    }

    return EXIT_SUCCESS;
}
