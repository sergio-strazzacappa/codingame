#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "strategy.h"
#include "entities.h"
#include "output.h"
#include "map.h"

task_t tasks[MAX_TASKS];
size_t task_count;

int cmp(const void *a, const void *b) {
    task_t *t1 = (task_t *)a;
    task_t *t2 = (task_t *)b;

    if (t1->cost < t2->cost)
        return -1;
    else if (t1->cost > t2->cost)
        return 1;
    else
        return 0;
}

void compute_tasks(void) {
    task_count = 0;

    for (size_t i = 0; i < my_troll_count; i++) {
        troll_t troll = my_trolls[i];

        // add more tasks
        for (size_t j = 0; j < tree_count; j++) {
            point_t target = trees[j].p;
            int dist = pathfinding(&troll.p, &target, NULL);

            tasks[task_count++] = (task_t){troll.id, target, dist};
        }
    }

    // sort the tasks by cost
    qsort(tasks, task_count, sizeof(tasks[0]), cmp);

    // assign tasks
    int troll_assigned[MAX_TROLLS] = {0};
    point_t task_assigned[MAX_TASKS] = {0};
    size_t tasks_tracked = 0;

    for (size_t i = 0; i < MAX_TASKS; i++) {
        task_t t = tasks[i];
        bool t_free = true;

        for (size_t j = 0; j < tasks_tracked && t_free; j++) {
            if (t.troll_id == troll_assigned[j]) {
                t_free = false;
                continue;
            }

            if (point_equal(&t.pos, &task_assigned[j])) {
                t_free = false;
                continue;
            }
        }

        // TODO: Check why pathfinding next value is the same as the target
        if (t_free) {
            troll_assigned[tasks_tracked] = t.troll_id;
            task_assigned[tasks_tracked] = t.pos;
            tasks_tracked++;
            point_t *next = (point_t *) malloc(sizeof(point_t));
            pathfinding(&t.pos, &t.pos, next);
            fprintf(stderr, "(%d, %d) - (%d, %d)\n", t.pos.x, t.pos.y, next->x, next->y);
            action_move(t.troll_id, next);
        }
    }
}

/*
 *
 */
int pathfinding(const point_t *start, const point_t *end, point_t *next) {
    // start and end are the same cell
    if (point_equal(start, end)) {
        if (next != NULL)
            *next = *end;
        return 0;
    }

    bool visited[MAX_HEIGHT][MAX_WIDTH] = {false};

    node_t queue[MAX_HEIGHT * MAX_WIDTH];
    size_t head = 0;
    size_t tail = 0;

    // queue the starting point
    queue[tail++] = (node_t){*start, -1, 0};
    visited[start->y][start->x] = true;

    int target_idx = -1;

    while (head < tail) {
        int current_idx = (int)head;
        node_t n = queue[head++];

        if (point_equal(&(n.current), end)) {
            target_idx = current_idx;
            break;
        }

        for (size_t i = 0; i < 4; i++) {
            point_t p = {n.current.x + DIRS[i][0], n.current.y + DIRS[i][1]};

            if (p.x < 0)
                continue;
            if (p.x >= (int)cols)
                continue;
            if (p.y < 0)
                continue;
            if (p.y >= (int)rows)
                continue;
            if (!walkable(&p))
                continue;
            if (visited[p.y][p.x])
                continue;

            assert(tail < rows * cols);

            // add the nodes to the frontier
            visited[p.y][p.x] = true;
            queue[tail++] = (node_t){p, current_idx, n.distance + 1};
        }
    }

    if (target_idx != -1) {
        int curr = target_idx;

        if (next != NULL) {
            while (queue[curr].parent_idx != 0) {
                curr = queue[curr].parent_idx;
            }

            *next = queue[curr].current;
        }

        return queue[target_idx].distance;
    }

    // unreachable
    return -1;
}

// return true if point p is a tree and fruits > 0
bool is_tree(const point_t *p) {
    for (size_t i = 0; i < tree_count; i++) {
        tree_t t = trees[i];

        if (t.p.x == p->x && t.p.y == p->y && t.fruits > 0)
            return true;
    }

    return false;
}

// return true if troll t capacity is full
bool is_troll_full(const troll_t *t) {
    int carry =
        t->carry_plum + t->carry_lemon + t->carry_apple + t->carry_banana +
        t->carry_iron + t->carry_wood;

    return carry >= t->carry_capacity;
}

void chopper(const troll_t *t) {
    for (size_t i = 0; i < tree_count; i++) {
        fprintf(stderr, "(%d, %d) -> %d\n", trees[i].p.x, trees[i].p.y, trees[i].claimed);
    }
    point_t *next = (point_t*) malloc(sizeof(point_t));

    for (size_t i = 0; i < tree_count; i++) {
        if (point_equal(&t->p, &trees[i].p)) {
            trees[i].claimed = true;
            action_chop(t->id);
            return;
        }
    }

    if (!is_troll_full(t)) {
        size_t closest = INT_MAX;
        size_t target = 0;
        point_t next_move = {0};

        for (size_t i = 0; i < tree_count; i++) {
            if (trees[i].claimed)
                continue;

            int d = pathfinding(&(t->p), &(trees[i].p), next);

            if (d < closest) {
                closest = d;
                target = i;
                next_move = *next;
            }
        }

        if (closest == 0) {
            trees[target].claimed = true;
            action_chop(t->id);
            return;
        }

        trees[target].claimed = true;
        fprintf(stderr, "Move %d -> (%d, %d)\n", t->id, trees[target].p.x, trees[target].p.y);
        action_move(t->id, &next_move);
        return;
    }

    int d = pathfinding(&(t->p), &my_shack, next);
    fprintf(stderr, "Return %d\n", d);

    if (d == 1) {
        action_drop(t->id);
        return;
    }

    action_move(t->id, next);
}

void train_troll(void) {
    /*
     * basic train function: train the min chopper
     *
     * movement_speed 1 = my_troll_count + 1 plum
     * carry_capacity 1 = my_troll_count + 1 lemon
     * harvest_power 0 = my_troll_count apple
     * chop_power 1 = my_troll_count + 1 iron
     */

    if ((size_t)me.plums < my_troll_count + 1)
        return;

    if ((size_t)me.lemons < my_troll_count + 1)
        return;

    if ((size_t)me.apples < my_troll_count)
        return;

    if ((size_t)me.iron < my_troll_count + 1)
        return;

    action_train(1, 1, 0, 1);
}

/*
 ******************************************************************************
 ******************************** DEBUG FUNCTIONS *****************************
 ******************************************************************************
 */

void print_tasks(void) {
    for (size_t i = 0; i < task_count; i++) {
        task_t t = tasks[i];
        fprintf(stderr, "[DEBUG] Task %zu: [%d, (%d, %d), %d]\n",
            i + 1, t.troll_id, t.pos.x, t.pos.y, t.cost);
    }
}
