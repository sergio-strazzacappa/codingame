#ifndef GAME_H
#define GAME_H

#define MAX_HEIGHT      8
#define MAX_WIDTH       ((MAX_HEIGHT) * 2)
#define OPTIMAL_TRAIN   1

typedef enum status_e {
    TO_TREE,
    HARVEST,
    RETURN,
    DROP
} status_t;

typedef struct point_s {
    int x;
    int y;
} point_t;

extern int turn;

#endif /* GAME_H */
