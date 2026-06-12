#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/time.h>
#include <math.h>
#include <assert.h>
#include "beam.h"

const int FIB[] = {
    1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584,
    4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811,
    514229, 832040, 1346269, 2178309, 3524578, 5702887
};

size_t pool_count;
Node pool[POOL_SIZE];

void run(void) {
    pool_count = 0;
    struct timeval start;

    gettimeofday(&start, NULL);

    // create the root of the tree
    State root =
        create_state(ash, human_count, humans, zombie_count, zombies, 0);
    init_tree(&root);

    // queue of current nodes to expand
    int frontier[MAX_STATES];
    size_t head = 0;
    size_t tail = 0;

    // append the root to the frontier
    frontier[tail++] = 0;

    size_t depth = 1;
    bool ended = false;
    while (depth <= BEAM_MAX_DEPTH && !ended) {
        struct timeval end;
        gettimeofday(&end, NULL);
        double ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                    (end.tv_usec - start.tv_usec) / 1000.0;

        fprintf(stderr, "[DEBUG] Elapsed time %.2fms\n", ms);

        if (ms >= TIME_LIMIT) {
            fprintf(stderr, "[DEBUG] TIME OUT\n");
            break;
        }

        if (DEBUG)
            fprintf(stderr, "[DEBUG] DEPTH %zu\n", depth);

        ended = true;

        // frontier for the candidates of the next depth
        Node next_frontier[MAX_STATES] = {};
        size_t next_tail = 0;

        while (head < tail) {
            int tmp_index = 0;
            int current_pool_idx = frontier[head++];
            Node current = pool[current_pool_idx];

            if (n_live_zombies(&current.s) == 0)
                continue;
            if (n_live_humans(&current.s) == 0)
                continue;

            ended = false;

            // stay
            State s = next_state(&current.s, current.s.ash, depth);
            Node n = {tmp_index++, s, current.s.ash, current_pool_idx, true};
            next_frontier[next_tail++] = n;

            // move to every zombie
            for (size_t i = 0; i < current.s.zombie_count; i++) {
                if (current.s.zombies[i].dead)
                    continue;

                Point zombie_next;
                if (depth == 1)
                    zombie_next = current.s.zombies[i].next;
                else
                    zombie_next = move_zombie(current.s.zombies[i].pos, &current.s);

                s = next_state(&current.s, zombie_next, depth);
                n = (Node){tmp_index++, s, zombie_next, current_pool_idx, true};
                next_frontier[next_tail++] = n;
            }

            // move to every human
            for (size_t i = 0; i < current.s.human_count; i++) {
                if (current.s.humans[i].dead)
                    continue;

                s = next_state(&current.s, current.s.humans[i].pos, depth);
                n = (Node){
                    tmp_index++, s, current.s.humans[i].pos, current_pool_idx,
                    true 
                };
                next_frontier[next_tail++] = n;
            }

            // move to every cell in the middle between a human and a zombie
            for (size_t i = 0; i < current.s.zombie_count; i++) {
                if (next_tail >= MAX_STATES)
                    break;
                if (current.s.zombies[i].dead)
                    continue;
                for (size_t j = 0; j < current.s.human_count; j++) {
                    if (current.s.humans[j].dead)
                        continue;

                    int x = (int)(current.s.zombies[i].pos.x +
                            current.s.humans[j].pos.x) / 2;
                    int y = (int)(current.s.zombies[i].pos.y +
                            current.s.humans[j].pos.y) / 2;

                    Point p = {x, y};
                    s = next_state(&current.s, p, depth);
                    n = (Node){tmp_index++, s, p, current_pool_idx, true};
                    next_frontier[next_tail++] = n;
                }
            }
            pool[current_pool_idx].is_leaf = false;
        }

        // generate the queue for the next depth
        qsort(next_frontier, next_tail, sizeof(Node), cmp);

        head = 0;
        tail = 0;

        if (DEBUG) {
            fprintf(stderr, "[DEBUG] next_queue:\n");

            for (size_t i = 0; i < next_tail; i++) {
                Node nn = next_frontier[i];
                fprintf(stderr,
                    "[DEBUG] [ Ash=(%d, %d), action=(%d, %d), parent=%d, eval=%.2f]\n",
                    nn.s.ash.x, nn.s.ash.y,
                    nn.action.x, nn.action.y,
                    nn.parent, nn.s.eval);
            }
        }

        // set the indexes of the next depth and add the nodes to the tree
        size_t k = MIN(next_tail, BEAM_K);

        next_frontier[0].id = pool_count;
        pool[pool_count] = next_frontier[0];
        frontier[tail++] = pool_count;
        pool_count++;
        size_t saved_nodes = 1;

        for (size_t i = 1; i < next_tail; i++) {
            if (saved_nodes == k)
                break;

            if (node_equal(&next_frontier[i], &pool[pool_count - 1]))
                continue;
            
            next_frontier[i].id = pool_count;
            pool[pool_count] = next_frontier[i];
            frontier[tail++] = pool_count;
            pool_count++;
            saved_nodes++;
        }

        depth++;

        if (DEBUG)
            print_tree_structure();

    }

    // get the index of max evaluation
    double max_eval = -INF;
    int index = 0;

    for (size_t i = 0; i < pool_count; i++) {
        if (!pool[i].is_leaf)
            continue;

        if (pool[i].s.eval > max_eval) {
            max_eval = pool[i].s.eval;
            index = i;
        }
    }

    assert(max_eval != -INF);

    if (DEBUG)
        fprintf(stderr,
            "[DEBUG] Index of node %d with max eval %.2f\n",
            index, pool[index].s.eval);

    // rebuld the path
    int best_move = index;

    while (index != -1 && pool[index].parent != 0) 
        index = pool[index].parent;

    if (index != -1)
        best_move = index;

    fprintf(stderr, "[DEBUG] Best move %d at depth %zu\n", best_move, depth);
    fprintf(stderr, "[DEBUG] Final Eval %f\n", pool[best_move].s.eval);
    fprintf(stderr, "[DEBUG] Final Score %d\n", pool[best_move].s.score);

    printf("%d %d\n", pool[best_move].action.x, pool[best_move].action.y);
}

// TREE ------------------------------------------------------------------------

State create_state(const Point ash,
    const size_t human_count, const Human humans[],
    const size_t zombie_count, const Zombie zombies[],
    const int parent_score) {

    State s;

    s.ash = ash;
    s.human_count = human_count;
    memcpy(s.humans, humans, sizeof(humans[0]) * human_count);
    s.zombie_count = zombie_count;
    memcpy(s.zombies, zombies, sizeof(zombies[0]) * zombie_count);
    s.score = parent_score; 
    s.eval = h(&s);

    return s;
}

void init_tree(const State *root) {
    Node n;
    n.id = 0;
    n.s = *root;
    n.action = (Point){-1, -1};
    n.parent = -1;
    n.is_leaf = true;

    pool_count = 0;
    pool[pool_count++] = n;
}

State clone_state(const State *s) {
    State new;

    new.ash = s->ash;

    new.human_count = s->human_count;
    memcpy(new.humans, s->humans, s->human_count * sizeof(Human));

    new.zombie_count = s->zombie_count;
    memcpy(new.zombies, s->zombies, s->zombie_count * sizeof(Zombie));

    new.score = s->score;
    new.eval = s->eval;

    return new;
}

bool node_equal(const Node *n1, const Node *n2) {
    // check ash position
    if (n1->s.ash.x != n2->s.ash.x)
        return false;
    if (n1->s.ash.y != n2->s.ash.y)
        return false;

    // check the number of humans alive
    if (n_live_humans(&n1->s) != n_live_humans(&n2->s))
        return false;

    // check the zombies positions
    for (size_t i = 0; i < n1->s.zombie_count; i++) {
        Zombie z1 = n1->s.zombies[i];
        Zombie z2 = n2->s.zombies[i];

        if (z1.dead != z2.dead)
            return false;
        if (z1.pos.x != z2.pos.x)
            return false;
        if (z1.pos.y != z2.pos.y)
            return false;
    }

    return true;
}

// GAME ------------------------------------------------------------------------

// simulate one turn
State next_state(const State *s, const Point target, const size_t depth) {
    assert(target.x >= 0 && target.x <= COLS);
    assert(target.y >= 0 && target.y <= ROWS);

    State next = clone_state(s);

    /*
     * order of actions:
     * 1 - move the zombies
     * 2 - move ash
     * 3 - kill the zombies
     * 4 - kill the humans
     */

    // move the zombies
    for (size_t i = 0; i < s->zombie_count; i++) {
        if (s->zombies[i].dead)
            continue;

        if (depth == 1)
            next.zombies[i].pos = s->zombies[i].next;
        else
            next.zombies[i].pos = move_zombie(s->zombies[i].pos, s);
    }

    // move ash
    next.ash = move(s->ash, target, 1000);

    // kill zombies
    size_t killed = 0;
    for (size_t i = 0; i < next.zombie_count; i++) {
        if (next.zombies[i].dead)
            continue;

        if (distance(next.ash, next.zombies[i].pos) - EPSILON <= 2000) {
            killed++;
            next.zombies[i].dead = true;
        }
    }

    // kill humans
    for (size_t i = 0; i < next.zombie_count; i++) {
        if (next.zombies[i].dead)
            continue;

        for (size_t j = 0; j < next.human_count; j++) {
            if (next.humans[j].dead)
                continue;

            if (next.zombies[i].pos.x == next.humans[j].pos.x &&
                next.zombies[i].pos.y == next.humans[j].pos.y) {

                next.humans[j].dead = true;
            }
        }
    }

    // evaluate the next state
    next.score = score(&next, s->score, killed);
    next.eval = h(&next);

    return next;
}

Point move(const Point from, const Point to, const int limit) {
    double dist = distance(from, to);

    if (from.x == to.x && from.y == to.y)
        return to;

    if (dist - EPSILON <= limit) {
        return to;
    } else {
        int dx = to.x - from.x;
        int dy = to.y - from.y;

        assert(dist != 0);

       return (Point){
           (int)floor((double)(from.x + dx * (double)limit / dist)),
           (int)floor((double)(from.y + dy * (double)limit / dist)),
        };
    }
}

Point move_zombie(const Point from, const State *s) {
    // move to the closest target of ash and the humans
    double dist = distance(from, s->ash);
    Point zombie_target = s->ash;
    int min_distance = dist;

    for (size_t i = 0; i < s->human_count; i++) {
        if (s->humans[i].dead)
            continue;

        dist = distance(from, s->humans[i].pos);

        if (dist < min_distance) {
            min_distance = dist;
            zombie_target = s->humans[i].pos; 
        }
    }

    return move(from, zombie_target, 400);
}

// calculate the score ash can get in the current state + the overall in the
// previous turns
int score(const State *s, const int parent_score, const size_t kills) {
    int live = n_live_humans(s);
    int points = parent_score;
    int zombie_score = live * live * 10;

    for (size_t i = 0; i < kills; i++)
        points += zombie_score * FIB[i];

    return points;
}

double h(const State *s) {
    /* Increase -> score accumulated in previous turns
     * Decrease -> dead humans
     * Decrease -> distance of ash from the dangerous zombie
     */

    int live_humans = n_live_humans(s);
    int live_zombies = n_live_zombies(s);

    if (live_humans == 0)
        return -INF + s->score;
    if (live_zombies == 0)
        return INF + s->score;

    // update the score -> previous score + current score
    double points = s->score; 

    // decrease the score for dead humans
    points -= (s->human_count - live_humans) * 4000000.0;

    // mark dead future dead humans
    bool dead[MAX_HUMANS];

    for (size_t i = 0; i < s->human_count; i++) {
        dead[i] = false;

        if (s->humans[i].dead) {
            dead[i] = true;
            continue;
        }

        double human_to_ash = distance(s->humans[i].pos, s->ash);

        for (size_t j = 0; j < zombie_count; j++) {
            if (s->zombies[j].dead)
                continue;

            double human_to_zombie = distance(s->humans[i].pos, s->zombies[j].pos);

            if (human_to_ash > human_to_zombie) {
                dead[i] = true;
                points -= 4000000.0;
                break;
            }
        }
    }

    // decrease the score if ash is far from the dangerous zombie
    int min_distance_ash_zombie = INF;
    for (size_t i = 0; i < s->zombie_count; i++) {
        if (s->zombies[i].dead)
            continue;

        double d = distance(s->ash, s->zombies[i].pos);

        if (d < min_distance_ash_zombie)
            min_distance_ash_zombie = d;

        // find the dangerous zombie
        int min_distance_human_zombie = INF;
        for (size_t j = 0; j < s->human_count; j++) {
            if (s->humans[j].dead || dead[j])
                continue;

            d = distance(s->humans[j].pos, s->zombies[i].pos);

            if (d < min_distance_human_zombie)
                min_distance_human_zombie = d;
        }

        if (min_distance_human_zombie != INF) {
            points -= min_distance_ash_zombie / 10.0;

            if (min_distance_human_zombie < 800)
                points -= (800 - min_distance_human_zombie) * 5;
        }
    }

    if (min_distance_ash_zombie != INF)
        points -= (min_distance_ash_zombie / 2.0);

    return points;
}

int n_live_humans(const State *s) {
    int n = 0;

    for (size_t i = 0; i < s->human_count; i++) {
        if (!s->humans[i].dead)
            n++;
    }

    return n;
}

int n_live_zombies(const State *s) {
    int n = 0;

    for (size_t i = 0; i < s->zombie_count; i++) {
        if (!s->zombies[i].dead)
            n++;
    }

    return n;
}

double distance(const Point p, const Point q) {
    return hypot(p.x - q.x, p.y - q.y);
}

int cmp(const void *a, const void *b) {
    const Node *n1 = (Node *)a;
    const Node *n2 = (Node *)b;

    if (n1->s.eval > n2->s.eval)
        return -1;
    else if (n1->s.eval < n2->s.eval)
        return 1;
    else if (n1->id < n2->id)
        return 1;
    else
        return -1;
}

void print_tree(void) {
    for (size_t i = 0; i < pool_count; i++) {
        fprintf(stderr, "----- Start node at %zu -----\n", i);
        print_node(&pool[i]);
        fprintf(stderr, "----- End node at %zu -----\n", i);
    }
}

void print_node(const Node *n) {
    print_state(&(n->s));

    fprintf(stderr, "Parent = %d\n", n->parent);
    fprintf(stderr, "Action = (%d, %d)\n", n->action.x, n->action.y);
    fprintf(stderr, "is_leaf = %s\n", DEAD[n->is_leaf]);
}

void print_state(const State *s) {
    fprintf(stderr, "[DEBUG] Ash = (%d, %d)\n", s->ash.x, s->ash.y);

    fprintf(stderr, "[DEBUG] human_count = %zu\n", s->human_count);
    print_humans(s->humans);

    fprintf(stderr, "[DEBUG] zombie_count = %zu\n", s->zombie_count);
    print_zombies(s->zombies);

    fprintf(stderr, "[DEBUG] Eval = %.2f\n", s->eval);
}

void print_tree_structure(void) {
    for (size_t i = 0; i < pool_count; i++) {
        fprintf(stderr, "[DEBUG] node at %3d [MOVE to (%5d, %5d) target (%5d, %5d) - score = %4d - eval = %12.2f] - parent -> %3d - is_leaf %s\n",
            pool[i].id, pool[i].s.ash.x, pool[i].s.ash.y,
            pool[i].action.x, pool[i].action.y, pool[i].s.score, pool[i].s.eval, pool[i].parent,
            DEAD[pool[i].is_leaf]);

        fprintf(stderr, "[DEBUG] Zombies: [ ");
        for (size_t j = 0; j < pool[i].s.zombie_count; j++) {
            fprintf(stderr, " (%d, %d)", pool[i].s.zombies[j].pos.x, pool[i].s.zombies[j].pos.y);
        }
        fprintf(stderr, " ]\n\n");
    }
}
