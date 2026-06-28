#include "entities.h"
#include "game.h"
#include "greedy.h" // change to the algorithm used
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void simulation(void) {
    size_t points = 0;
    size_t turn = 0;
    read_input();

    while (true) {
        fprintf(stderr, "[GAME] START OF TURN %zu\n", turn);
        print_ash();
        print_humans(humans, human_count);
        print_zombies(zombies, zombie_count);

        if (human_count == 0) {
            printf("[GAME] YOU LOST\n");
            break;
        }

        if (zombie_count == 0) {
            printf("[GAME] YOU WIN %zu POINTS\n", points);
            break;
        }

        // calculate ash next move
        Point next_move = move(ash, run(), ASH_SPEED);

        Point h[human_count];
        for (size_t i = 0; i < human_count; i++)
            h[i] = humans[i].pos;

        // move the zombies
        for (size_t i = 0; i < zombie_count; i++)
            zombies[i].pos = move_zombie(zombies[i].pos, h, human_count, ash);

        // move ash
        ash = next_move;

        // kill the zombies
        size_t kills = kill_zombies(ash);
        zombie_count -= kills;

        // update the score
        for (size_t i = 0; i < kills; i++)
            points += human_count * human_count * 10 * FIB[i];

        // kill the humans
        human_count -= kill_humans();

        for (size_t i = 0; i < human_count; i++)
            h[i] = humans[i].pos;

        for (size_t i = 0; i < zombie_count; i++) {
            zombies[i].next_pos =
                move_zombie(zombies[i].pos, h, human_count, ash);
        }

        fprintf(stderr, "[DEBUG] Points: %zu\n", points);
        turn++;
    }
}

void exec(void) {
    while (true) {
        read_input();
        print_ash();
        print_humans(humans, human_count);
        print_zombies(zombies, zombie_count);
        Point next_move = run();
        printf("%d %d\n", next_move.x, next_move.y);
    }
}

int main(void) {
    // simulation();
    exec();
    return EXIT_SUCCESS;
}
