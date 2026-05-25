#include <stdio.h>
#include "entities.h"

Point ash;

size_t human_count;
Human humans[MAX_HUMANS];

size_t zombie_count;
Zombie zombies[MAX_ZOMBIES];

void read_input(void) {
    scanf("%d%d", &ash.x, &ash.y);

    scanf("%zu", &human_count);
    for (size_t i = 0; i < human_count; i++)
        scanf("%d%d%d", &humans[i].id, &humans[i].pos.x, &humans[i].pos.y);

    scanf("%zu", &zombie_count);
    for (size_t i = 0; i < zombie_count; i++)
        scanf("%d%d%d%d%d",
            &zombies[i].id,
            &zombies[i].pos.x, &zombies[i].pos.y,
            &zombies[i].next.x, &zombies[i].next.y);
}

void print_ash(void) {
    fprintf(stderr, "[DEBUG] Ash: (%d, %d)\n", ash.x, ash.y);
}

void print_humans(void) {
    fprintf(stderr, "[DEBUG] Humans:\n");

    for (size_t i = 0; i < human_count; i++)
        fprintf(stderr, "\t %d -> (%d, %d)\n",
                humans[i].id, humans[i].pos.x, humans[i].pos.y);
}

void print_zombies(void) {
    fprintf(stderr, "[DEBUG] Zombies:\n");

    for (size_t i = 0; i < zombie_count; i++)
        fprintf(stderr, "\t %d -> (%d, %d) - (%d, %d)\n",
                zombies[i].id,
                zombies[i].pos.x, zombies[i].pos.y,
                zombies[i].next.x, zombies[i].next.y);
}
