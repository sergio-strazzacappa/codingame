#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "entities.h"
#include "strategy.h"
#include "game.h"

int main(void) {
    while (true) {
        time_t start, end;

        start = clock();

        read_input();

        print_ash();
        print_humans(humans);
        print_zombies(zombies);

        if (ALG == GREEDY)
            greedy();
        if (ALG == BEAM_SEARCH)
            beam_search();

        end = clock();
        double ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

        printf(" %.2fms\n", ms);

        if (ONE_TURN)
            break; // run only one turn
    }

    return EXIT_SUCCESS;
}
