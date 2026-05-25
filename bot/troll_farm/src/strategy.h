#ifndef STRATEGY_H
#define STRATEGY_H

#include "map.h"
#include "entities.h"

typedef enum task_e {
    HARVEST,
    CHOP,
    MINE
} task_enum;

typedef struct task_s {
    int troll_id;
    point_t pos;
    double cost;
    task_enum t;
} task_t;

extern task_t tasks[MAX_TASKS];
extern size_t task_count;
extern int iron_needed;

void plant(const size_t turn);
void send(void);
void compute_tasks(const size_t turn);
void train_troll(void);

// ADD TASKS
void add_harvest(void);
void add_chop(const size_t turn);
void add_mine(void);

void assign_task(void);

// UTILITIES
int cmp(const void *a, const void *b);

point_t *get_troll_pos(const int id);
bool is_troll_full(const troll_t *t);

// DEBUG
void print_tasks(void);

#endif /* STRATRGY_H*/
