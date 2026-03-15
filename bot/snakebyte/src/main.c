#include <stdlib.h>
#include <string.h>
#include "../../../lib/ds/include/matrix.h"
#include "../include/io.h"
#include "../include/data.h"

int my_id;
char *starting_map = NULL;
char *map = NULL;
snakebot_t *my_bots;
snakebot_t *opp_bots;
size_t bots_per_player;
point_t *powers;
size_t powers_size;

void copy_map(void) {
    int rows = mat_get_rows(starting_map);
    int cols = mat_get_cols(starting_map);
    mat_init(map, rows, cols, sizeof(char));
    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            mat_insert(map, y, x, mat_get(starting_map, y, x));
        }
    }
}

void clean(void) {
    free(powers);
    
    for (size_t i = 0; i < bots_per_player; i++) {
        if (my_bots[i].body_len > 0) {
            free(my_bots[i].body);
            my_bots[i].body_len = 0;
        }

        if (opp_bots[i].body_len > 0) {
            free(opp_bots[i].body);
            opp_bots[i].body_len = 0;
        }
    }

    mat_free(map);
}

void loop(void) {
    while (1) {
        copy_map();
        read_turn();
        print_map();
        print_bots(my_bots, "My bots");
        print_bots(opp_bots, "Opp bots");

        /*
         * run an algorithm, print the next action
         */
        printf("WAIT\n");
        clean();
    }
}

int main(void) {
    read_init();
    loop();
    mat_free(starting_map);

    return EXIT_SUCCESS;
}
