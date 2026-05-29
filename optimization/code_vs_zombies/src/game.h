#ifndef GAME_H
#define GAME_H

// game params
#define ALG             BEAM_SEARCH

typedef enum {
    GREEDY,
    BEAM_SEARCH
} Algorithm;

#define MAX_HUMANS      99
#define MAX_ZOMBIES     99
#define ROWS            9000
#define COLS            16000

// bean search params
#define POOL_SIZE       4096
#define MAX_STATES      2048
#define BEAM_K          10
#define BEAM_MAX_DEPTH  20

// general params
#define INF             9999
#define DEBUG           true
#define MIN(a, b)       ((a) < (b) ? (a) : (b))

#endif /* GAME_H */
