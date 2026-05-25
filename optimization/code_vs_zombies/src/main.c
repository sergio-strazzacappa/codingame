#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "entities.h"

int main(void) {
    while (true) {
        read_input();

        print_ash();
        print_humans();
        print_zombies();
    }

    return EXIT_SUCCESS;
}
