#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "strategy.h"
#include "entities.h"
#include "output.h"
#include "map.h"

task_t tasks[MAX_TASKS];
size_t task_count;

int iron_needed;

void plant(const size_t turn) {
    if (turn >= PLANT_LIMIT)
        return;

    size_t n = 0;
    size_t n_plums = 0;
    size_t n_lemons = 0;
    size_t n_apples = 0;
    size_t n_bananas = 0;

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            point_t p = {x, y};
            for (size_t i = 0; i < tree_count; i++) {
                if (point_equal(&trees[i].p, &p) && distances_from_shack[y][x] <= 2) {
                    n++;
                    if (trees[i].type == PLUM)
                        n_plums++;
                    if (trees[i].type == LEMON)
                        n_lemons++;
                    if (trees[i].type == APPLE)
                        n_apples++;
                    if (trees[i].type == BANANA)
                        n_bananas++;
                    break;
                }
            }
        }
    }

    if (n > 5)
        return;

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            point_t target = {x, y};

            if (distances_from_shack[y][x] > 2)
                continue;
            if (grid[y][x] != '.')
                continue;
            if (is_tree(&target))
                continue;

            for (size_t i = 0; i < my_troll_count; i++) {
                if (my_trolls[i].busy)
                    continue;
                if (my_trolls[i].carry_wood > 0)
                    continue;
                if (my_trolls[i].carry_iron > 0)
                    continue;

                troll_t t = my_trolls[i];

                if (is_troll_empty(&t)) {
                    if (distances_from_shack[t.p.y][t.p.x] <= 1 && !is_shack_empty()) {
                        // pick from the shack
                        
                        if (me.plums > 0 && n_plums <= n_lemons && n_plums <= n_apples && n_plums <= n_bananas) 
                            action_pick(t.id, "PLUM");
                        else if (me.lemons > 0 && n_lemons <= n_plums && n_lemons <= n_apples && n_lemons <= n_bananas)
                            action_pick(t.id, "LEMON");
                        else if (me.apples > 0 && n_apples <= n_plums && n_apples <= n_lemons && n_apples <= n_bananas)
                            action_pick(t.id, "APPLE");
                        else if (me.bananas > 0 && n_bananas <= n_plums && n_bananas <= n_lemons && n_bananas <= n_apples)
                            action_pick(t.id, "BANANA");
                        my_trolls[i].busy = true;
                        break;
                    }

                    for (size_t j = 0; j < tree_count; j++) {
                        if (point_equal(&t.p, &trees[j].p) && trees[j].fruits > 0) {
                            // harvest from a tree
                            action_harvest(t.id);
                            my_trolls[i].busy = true;
                            break;
                        }
                    }

                    if (my_trolls[i].busy)
                        break;

                    // search the closest source of seed
                    int closest = INF;
                    point_t best_target = {0, 0};
                    point_t next;

                    int d = pathfinding(&t.p, &my_shack, &next);

                    if (d != -1 && d < closest) {
                        closest = d;
                        best_target = next;
                    }

                    for (size_t j = 0; j < tree_count; j++) {
                        if (trees[j].fruits > 0) {
                            d = pathfinding(&t.p, &trees[j].p, &next);

                            if (d != -1 && d < closest) {
                                closest  = d;
                                best_target = next;
                            }
                        }
                    }

                    action_move(t.id, &best_target);
                    fprintf(stderr, "Move to (%d, %d)\n", tasks[i].pos.x, tasks[i].pos.y);
                    next_turn[i] = best_target;
                    my_trolls[i].busy = true;
                    break;
                } else if (point_equal(&t.p, &target)) {
                    // in empty cell
                    if (t.carry_plum)
                        action_plant(t.id, "PLUM");
                    else if (t.carry_lemon)
                        action_plant(t.id, "LEMON");
                    else if (t.carry_apple)
                        action_plant(t.id, "APPLE");
                    else if (t.carry_banana)
                        action_plant(t.id, "BANANA");
                    my_trolls[i].busy = true;
                    break;
                } else {
                    // walk toward the target
                    point_t next;
                    int d = pathfinding(&t.p, &target, &next);

                    if (d == -1)
                        continue;

                    action_move(t.id, &next);
                    fprintf(stderr, "Move to (%d, %d)\n", target.x, target.y);
                    next_turn[i] = next;
                    my_trolls[i].busy = true;
                    break;
                }
            }
        }
    }
}

void send(void) {
    for (size_t i = 0; i < my_troll_count; i++) {
        if (my_trolls[i].busy)
            continue;
        if (is_troll_full(&my_trolls[i])) {
            if (distances_from_shack[my_trolls[i].p.y][my_trolls[i].p.x] <= 1) {
                action_drop(my_trolls[i].id);
                my_trolls[i].busy = true;
                continue;
            }
            point_t next = {0, 0};
            int d = pathfinding(&my_trolls[i].p, &my_shack, &next);

            if (d == -1)
                continue;

            action_move(my_trolls[i].id, &next);
            fprintf(stderr, "Move to (%d, %d)\n", my_shack.x, my_shack.y);
            my_trolls[i].busy = true;
        }
    }
}

void compute_tasks(const size_t turn) {
    task_count = 0;
    add_harvest();
    add_chop(turn);
    add_mine();

    // sort the tasks by cost
    qsort(tasks, task_count, sizeof(tasks[0]), cmp);

    assign_task();
}

void train_troll(void) {
    /*
     * BASIC = (1, 1, 1, 0)
     *
     * basic train function: train the min chopper
     *
     * movement_speed 1 = my_troll_count + 1 plum
     * carry_capacity 1 = my_troll_count + 1 lemon
     * harvest_power 0 = my_troll_count apple
     * chop_power 1 = my_troll_count + 1 iron
     *
     * CHOPPER
     * (2, 2, 0, 1)
     * PLUM = troll + 4
     * LEMON = troll + 4
     * APPLE = troll
     * IRON = troll + 1
     */

    if (my_troll_count >= MAX_TRAIN)
        return;

    if ((size_t)me.plums < my_troll_count + 4)
        return;

    if ((size_t)me.lemons < my_troll_count + 4)
        return;

    if ((size_t)me.apples < my_troll_count)
        return;

    if ((size_t)me.iron < my_troll_count + 1)
        return;

    action_train(2, 2, 1, 1);
}

// ADD TASKS ------------------------------------------------------------------
void add_harvest(void) {
    for (size_t i = 0; i < tree_count; i++) {
        if (trees[i].fruits == 0)
            continue;

        for (size_t j = 0; j < my_troll_count; j++) {
            if (my_trolls[j].busy)
                continue;
            if (is_troll_full(&my_trolls[j]))
                continue;

            int d1 = manhattan_distance(&my_trolls[j].p, &trees[i].p); 
            int d2 = manhattan_distance(&trees[i].p, &my_shack); 
            //int d1 = pathfinding(&my_trolls[j].p, &trees[i].p, NULL);
            //int d2 = pathfinding(&trees[i].p, &my_shack, NULL);

            if (d1 == -1)
                d1 = INF;
            if (d2 == -1)
                d2 = INF;

            double cost = d1 + d2;

            fprintf(stderr, "(%d, %d) - %f\n", trees[i].p.x, trees[i].p.y, cost);

            if (my_troll_count < MAX_TRAIN) {
                if (trees[i].type == PLUM && me.plums <= me.lemons && me.plums <= me.apples && me .plums <= me.bananas)
                    cost = cost / 10 + me.plums / 4.;
                if (trees[i].type == LEMON && me.lemons <= me.plums && me.lemons <= me.apples && me .lemons <= me.bananas)
                    cost = cost / 10 + me.lemons / 4.;
                if (trees[i].type == APPLE && me.apples <= me.plums && me.apples <= me.lemons && me .apples <= me.bananas)
                    cost = cost / 10 + me.apples / 4.;
                if (trees[i].type == BANANA && me.bananas <= me.plums && me.bananas <= me.lemons && me.bananas <= me.apples)
                    cost = cost / 10 + me.bananas / 4.;
            } 

            tasks[task_count++] =
                (task_t){j, trees[i].p, cost, HARVEST};
        }
    }
}

void add_chop(const size_t turn) {
    if (turn < CHOP_LIMIT)
        return;

    for (size_t i = 0; i < tree_count; i++) {
        for (size_t j = 0; j < my_troll_count; j++) {
            if (my_trolls[j].busy)
                continue;

            point_t next = {0, 0};
            //int d = pathfinding(&my_trolls[j].p, &trees[i].p, &next);
            int d = manhattan_distance(&my_trolls[j].p, &trees[i].p);

            if (d == -1)
                d = INF;

            tasks[task_count++] = (task_t){j, trees[i].p, d / 2., CHOP};
        }
    } 
}

void add_mine(void) {
    if (my_troll_count >= MAX_TRAIN)
        iron_needed = 0;
    else
        iron_needed = my_troll_count + 1;

    int total_iron = me.iron;

    for (size_t i = 0; i < my_troll_count; i++) {
        total_iron += my_trolls[i].carry_iron;
    }

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {
            if (grid[y][x] != '+')
                continue;

            if (total_iron < iron_needed) {
                for (size_t i = 0; i < my_troll_count; i++) {
                    point_t mine = {x, y};
                    point_t next = {0, 0};
                    //int d = pathfinding(&my_trolls[i].p, &mine, &next);
                    int d = manhattan_distance(&my_trolls[i].p, &mine);

                    if (d == -1)
                        d = INF;

                    tasks[task_count++] = (task_t){i, mine, d / 10., MINE};
                }
            }
        }
    }
}

void assign_task(void) {
    for (size_t i = 0; i < task_count; i++) {
        troll_t t = my_trolls[tasks[i].troll_id];

        if (t.busy)
            continue;

        if (tasks[i].t == HARVEST) {
            if (point_equal(&t.p, &tasks[i].pos) && !is_troll_full(&t)) {
                action_harvest(t.id);
                my_trolls[tasks[i].troll_id].busy = true;
                continue;
            } else {
                point_t next = {0, 0};
                int d = pathfinding(&t.p, &tasks[i].pos, &next);

                if (d == -1)
                    continue;

                action_move(t.id, &next);
                fprintf(stderr, "Move to (%d, %d)\n", tasks[i].pos.x, tasks[i].pos.y);
                my_trolls[tasks[i].troll_id].busy = true;
            }
        } else if (tasks[i].t == CHOP) {
            if (point_equal(&t.p, &tasks[i].pos) && !is_troll_full(&t)) {
                action_chop(t.id);
                my_trolls[tasks[i].troll_id].busy = true;
                continue;
            } else {
                point_t next = {0, 0};
                int d = pathfinding(&t.p, &tasks[i].pos, &next);

                if (d == -1)
                    continue;

                action_move(t.id, &next);
                fprintf(stderr, "Move (%d, %d)\n", tasks[i].pos.x, tasks[i].pos.y);
                my_trolls[tasks[i].troll_id].busy = true;
            }
        } else if (tasks[i].t == MINE) {
            if (manhattan_distance(&t.p, &tasks[i].pos) == 1 && !is_troll_full(&t)) {
                action_mine(t.id);
                my_trolls[tasks[i].troll_id].busy = true;
                continue;
            } else {
                point_t next = {0, 0};
                int d = pathfinding(&t.p, &tasks[i].pos, &next);

                if (d == -1)
                    continue;

                action_move(t.id, &next);
                fprintf(stderr, "Move to mine (%d, %d)\n", tasks[i].pos.x, tasks[i].pos.y);
                my_trolls[tasks[i].troll_id].busy = true;
            }
        }
    }
}

// compare the cost of two task and order them in increase order
int cmp(const void *a, const void *b) {
    const task_t *t1 = (task_t *)a;
    const task_t *t2 = (task_t *)b;

    if (t1->cost < t2->cost)
        return -1;
    else if (t1->cost > t2->cost)
        return 1;
    else
        return 0;
}

// return the position in the map of the troll with the given id, NULL if not
// found
point_t *get_troll_pos(const int id) {
    for (size_t i = 0; i < my_troll_count; i++) {
        if (my_trolls[i].id == id)
            return &my_trolls[i].p;
    }

    return NULL;
}

// return true if troll t capacity is full
bool is_troll_full(const troll_t *t) {
    int carry =
        t->carry_plum + t->carry_lemon + t->carry_apple + t->carry_banana +
        t->carry_iron + t->carry_wood;

    return carry >= t->carry_capacity;
}

/*
 ******************************************************************************
 ******************************** DEBUG FUNCTIONS *****************************
 ******************************************************************************
 */

void print_tasks(void) {
    const char *TASK_TYPES[3] = {
        "HARVEST",
        "CHOP",
        "MINE"
    };

    for (size_t i = 0; i < task_count; i++) {
        task_t t = tasks[i];

        fprintf(stderr, "[DEBUG] Task %zu: [%d, (%d, %d), %.2f, %s]\n",
            i + 1, t.troll_id, t.pos.x, t.pos.y, t.cost, TASK_TYPES[t.t]);
    }
}
