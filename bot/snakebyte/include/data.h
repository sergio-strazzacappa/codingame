#ifndef DATA_H
#define DATA_H

#include <stddef.h>

typedef enum status_e {
    ALIVE   = 0,
    DEAD    = 1
} status_t;

typedef struct point_s {
    size_t x;
    size_t y;
} point_t;

typedef struct snakebot_s {
    int id;
    status_t status;
    point_t *body;
    size_t body_len;
} snakebot_t;

extern int my_id;
extern char *starting_map;
extern char *map;
extern snakebot_t *my_bots;
extern snakebot_t *opp_bots;
extern size_t bots_per_player;
extern point_t *powers;
extern size_t powers_size;

#endif /* DATA_H */
