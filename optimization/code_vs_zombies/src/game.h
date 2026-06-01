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

// beam search params
#define POOL_SIZE       4096
#define MAX_STATES      2048
#define BEAM_K          15
#define BEAM_MAX_DEPTH  30

// general params
#define INF             99999999
#define DEBUG           false
#define ONE_TURN        false
#define MIN(a, b)       ((a) < (b) ? (a) : (b))

#endif /* GAME_H */
