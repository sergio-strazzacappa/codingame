#ifndef GAME_H
#define GAME_H

// game params
#define ALG             BEAM_SEARCH

typedef enum {
    GREEDY,
    BEAM_SEARCH
} Algorithm;

#define MAX_HUMANS      100
#define MAX_ZOMBIES     100
#define ROWS            9000
#define COLS            16000

// beam search params
#define POOL_SIZE       200     // 1 + (BEAM_MAX_DEPTH * BEAM_K) 
#define MAX_STATES      2048    // BEAM_K * BRANCHING FACTOR
#define BEAM_K          12
#define BEAM_MAX_DEPTH  15
#define TIME_LIMIT      0.85

// general params
#define INF             9999999
#define EPSILON         1e-5
#define DEBUG           false
#define ONE_TURN        false
#define MIN(a, b)       ((a) < (b) ? (a) : (b))

#endif /* GAME_H */
