#ifndef GAME_H
#define GAME_H

#define MAX_HUMANS  99
#define MAX_ZOMBIES 99
#define ALG         BEAM_SEARCH
#define POOL_SIZE   256
#define INF         9999
#define ROWS        9000
#define COLS        16000
#define MAX_STATES  1024

typedef enum {
    GREEDY,
    BEAM_SEARCH
} Algorithm;

#endif /* GAME_H */
