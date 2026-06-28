#include "entities.h"
#include "game.h"
#include <math.h>
#include <stdio.h>

const int FIB[] = {1,      2,       3,       5,       8,      13,     21,
                   34,     55,      89,      144,     233,    377,    610,
                   987,    1597,    2584,    4181,    6765,   10946,  17711,
                   28657,  46368,   75025,   121393,  196418, 317811, 514229,
                   832040, 1346269, 2178309, 3524578, 5702887};

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
        scanf("%d%d%d%d%d", &zombies[i].id, &zombies[i].pos.x,
              &zombies[i].pos.y, &zombies[i].next_pos.x,
              &zombies[i].next_pos.y);
}

Point move(const Point from, const Point to, const int limit) {
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    if (dx * dx + dy * dy <= limit * limit)
        return to;

    double d = distance(from, to);
    Point target = {.x = (int)(from.x + dx * limit / d),
                    .y = (int)(from.y + dy * limit / d)};

    return target;
}

Point move_zombie(const Point zombie, const Point humans[], const size_t hc,
                  const Point ash) {
    int dx = zombie.x - ash.x;
    int dy = zombie.y - ash.y;
    int sq = dx * dx + dy * dy;

    int min_d = sq;
    Point target = ash;

    for (size_t i = 0; i < hc; i++) {
        dx = zombie.x - humans[i].x;
        dy = zombie.y - humans[i].y;
        sq = dx * dx + dy * dy;

        if (sq < min_d) {
            min_d = sq;
            target = humans[i];
        }
    }

    return move(zombie, target, ZOMBIE_SPEED);
}

size_t kill_zombies(const Point ash) {
    size_t killed = 0;
    size_t write_index = 0;

    for (size_t i = 0; i < zombie_count; i++) {
        int dx = ash.x - zombies[i].pos.x;
        int dy = ash.y - zombies[i].pos.y;

        if (dx * dx + dy * dy <= ASH_RADIUS * ASH_RADIUS) {
            killed++;
        } else {
            if (i != write_index) {
                zombies[write_index] = zombies[i];
            }
            write_index++;
        }
    }
    return killed;
}

size_t kill_humans(void) {
    size_t killed = 0;
    size_t write_index = 0;

    for (size_t i = 0; i < human_count; i++) {
        bool is_killed = false;

        for (size_t j = 0; j < zombie_count; j++) {
            if (humans[i].pos.x == zombies[j].pos.x &&
                humans[i].pos.y == zombies[j].pos.y) {
                killed++;
                is_killed = true;
                break;
            }
        }
        if (!is_killed) {
            if (i != write_index)
                humans[write_index] = humans[i];
            write_index++;
        }
    }
    return killed;
}

// return the euclidean distance between p and q using sqrt
double distance(const Point p, const Point q) {
    int dx = p.x - q.x;
    int dy = p.y - q.y;

    return sqrt(dx * dx + dy * dy);
}

// DEBUG -----------------------------------------------------------------------

void print_ash(void) {
    fprintf(stderr, "[DEBUG] Ash: (%d, %d)\n", ash.x, ash.y);
}

void print_humans(const Human humans[], size_t hc) {
    fprintf(stderr, "[DEBUG] Humans:\n");

    for (size_t i = 0; i < hc; i++)
        fprintf(stderr, "\t %d -> (%d, %d)\n", humans[i].id, humans[i].pos.x,
                humans[i].pos.y);
}

void print_zombies(const Zombie zombies[], const size_t zc) {
    fprintf(stderr, "[DEBUG] Zombies:\n");

    for (size_t i = 0; i < zc; i++)
        fprintf(stderr, "\t %d -> (%d, %d) -> (%d, %d)\n", zombies[i].id,
                zombies[i].pos.x, zombies[i].pos.y, zombies[i].next_pos.x,
                zombies[i].next_pos.y);
}
