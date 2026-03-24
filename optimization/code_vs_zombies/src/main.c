#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define MAX_HUMANS  99
#define MAX_ZOMBIES 99

typedef struct point_s {
    int x;
    int y;
} point_t;

typedef struct human_s {
    int id;
    point_t pos;
} human_t;

typedef struct zombie_s {
    int id;
    point_t pos;
    point_t next_pos;
} zombie_t;

point_t ash;

size_t human_count;
human_t humans[MAX_HUMANS];

size_t zombie_count;
zombie_t zombies[MAX_ZOMBIES];

void print_ash() {
    fprintf(stderr, "[DEBUG] Ash: (%d, %d)\n", ash.x, ash.y);
}

void print_humans() {
    fprintf(stderr, "[DEBUG] Humans:\n");

    for (size_t i = 0; i < human_count; i++) {
        human_t h = humans[i];
        fprintf(stderr, "\t %d -> (%d, %d)\n", h.id, h.pos.x, h.pos.y);
    }
}

void print_zombies() {
    fprintf(stderr, "[DEBUG] Zombies:\n");

    for (size_t i = 0; i < zombie_count; i++) {
        zombie_t z = zombies[i];
        fprintf(stderr, "\t %d -> (%d, %d) - (%d, %d)\n", z.id, z.pos.x, z.pos.y, z.next_pos.x, z.next_pos.y);
    }
}

void read_input() {
    scanf("%d%d", &ash.x, &ash.y);

    scanf("%zu", &human_count);
    for (size_t i = 0; i < human_count; i++) {
        human_t *h = &humans[i];
        scanf("%d%d%d", &h->id, &h->pos.x, &h->pos.y);
    }

    scanf("%zu", &zombie_count);
    for (size_t i = 0; i < zombie_count; i++) {
        zombie_t *z = &zombies[i];
        scanf("%d%d%d%d%d", &z->id, &z->pos.x, &z->pos.y, &z->next_pos.x, &z->next_pos.y);
    }
}

int main(void) {
    while (1) {
        read_input();
        /*
        print_ash();
        print_humans();
        print_zombies();
        */
    }

    return EXIT_SUCCESS;
}
