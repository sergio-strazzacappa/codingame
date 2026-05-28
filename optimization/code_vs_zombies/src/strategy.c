#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "strategy.h"

const int FIB[] = {
    1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584,
    4181, 6765
};

size_t pool_count;
Node pool[POOL_SIZE];

void greedy(void) {
    /*
     * Check for every human the distance to the closest zombie. The greedy
     * algorithm moves Ash towards the zombie that can kill a human sooner.
     * But if the human can't be saved (ash is too far) that human is discarded
     */
    Point target = {-1, -1};
    Point closest_human = {0, 0};
    int closest_human_distance = INF;
    int min_human = INF;

    for (size_t i = 0; i < human_count; i++) {
        int min_zombie = INF;
        Point target_zombie = {0, 0};
        bool found = true;

        double d = distance(ash, humans[i].pos) - 2000; // distance - radius
        int ash_turns = d <= 1000 ? 1 : d / 1000;

        if (d < closest_human_distance) {
            // save the closest human from Ash
            closest_human_distance = d;
            closest_human = humans[i].pos;
        }

        fprintf(stderr, "Ash reaches human (%d, %d) in %d turns\n",
            humans[i].pos.x, humans[i].pos.y, ash_turns);

        for (size_t j = 0; j < zombie_count; j++) {
            d = distance(humans[i].pos, zombies[j].pos);
            int turns_left = d <= 400 ? 1 : d / 400;

            if (turns_left < ash_turns) {
                // if the human can't be saved go to the next human, ignores
                // the next zombies
                fprintf(stderr, "Human at (%d, %d) is dead\n",
                    humans[i].pos.x, humans[i].pos.y);

                found = false;
                break;
            }

            if (turns_left < min_zombie) {
                // save the closest reachable zombie frim the current human
                min_zombie = turns_left;
                target_zombie = zombies[j].pos;
            }
        }

        if (found && min_zombie < min_human) {
            // the human can be saved
            target = target_zombie;
            min_human = min_zombie;
        }

        fprintf(stderr, "Human (%d, %d) dies in %d turns - found %d\n",
            humans[i].pos.x, humans[i].pos.y, min_zombie, found);
    }

    State s = create_state(ash, human_count, humans, zombie_count, zombies, 0);
    State n;

    if (target.x != -1) {
        // no human can be saved. Go to the closest human
        fprintf(stderr, "[INFO] Go to the zombie\n");

        n = next_state(&s, target);

        printf("%d %d", target.x, target.y);
    } else {
        fprintf(stderr, "[INFO] Go to the human\n");
        n = next_state(&s, closest_human);
        printf("%d %d", closest_human.x, closest_human.y);
    }

    print_state(&n);
}

void beam_search(void) {
    time_t start, end;

    start = clock();

    fprintf(stderr, "Start of beam search\n");

    // create the root of the tree
    init_tree(create_state(ash, human_count, humans, zombie_count, zombies, 0));
    size_t depth = 1;

    // queue of current nodes to expand
    int queue[MAX_STATES];
    size_t head = 0;
    size_t tail = 0;

    // append the root to the queue
    queue[tail++] = 0;

    size_t zombies_alive = zombie_count;

    while (depth <= BEAM_MAX_DEPTH) { // check exit conditions
        fprintf(stderr, "[DEBUG] \tDEPTH %zu\n", depth);

        // queue for the candidates of the next depth
        Node next_queue[MAX_STATES];
        size_t next_tail = 0;

        while (head < tail) {
            Node current = pool[queue[head++]];

            // move to every zombie
            for (size_t i = 0; i < current.s.zombie_count; i++) {
                if (current.s.zombies[i].dead)
                    continue;
                State s = next_state(&current.s, current.s.zombies[i].pos);
                next_queue[next_tail++] = (Node){s, current.s.zombies[i].pos, queue[head - 1]};
            }
        }

        // childs to keep
        int k = MIN(next_tail, BEAM_K);

        // generate the queue for the next depth
        qsort(next_queue, next_tail, sizeof(Node), cmp);

        head = 0;
        tail = 0;

        // set the indexes of the next depth and add the nodes to the tree
        for (size_t i = 0; (int)i < k; i++) {
            pool[pool_count] = next_queue[i];
            queue[tail++] = pool_count;
            pool_count++;
        }

        depth++;
        //print_tree();
    }

    int max_eval = pool[0].s.eval;
    int index = 0;

    for (size_t i = 1; i < pool_count; i++) {
        if (pool[i].s.eval >= max_eval) {
            max_eval = pool[i].s.eval;
            index = i;
        }
    }

    int parent = pool[index].parent;
    int best_move = 0;

    while (pool[parent].parent != -1) {
        best_move = parent;
        parent = pool[parent].parent;
    }

    printf("%d %d", pool[best_move].action.x, pool[best_move].action.y);

}

void init_tree(State root) {
    Node n;
    n.s = root;
    n.action = (Point){0, 0};
    n.parent = -1;

    pool_count = 0;
    pool[pool_count++] = n;
}

State create_state(const Point ash,
    const size_t human_count, const Human humans[],
    const size_t zombie_count, const Zombie zombies[],
    const double parent_eval) {

    State s;

    s.ash = ash;
    s.human_count = human_count;
    memcpy(s.humans, humans, sizeof(humans[0]) * human_count);
    s.zombie_count = zombie_count;
    memcpy(s.zombies, zombies, sizeof(zombies[0]) * zombie_count);
    s.eval = evaluate(&s, parent_eval);

    return s;
}

State next_state(const State *s, const Point target) {
    assert(target.x >= 0);
    assert(target.x <= COLS);
    assert(target.y >= 0);
    assert(target.y <= ROWS);

    State next = clone_state(s);


    // move the zombies
    for (size_t i = 0; i < next.zombie_count; i++) {
        if (next.zombies[i].dead)
            continue;
        double dist = distance(next.zombies[i].pos, next.ash);
        Point zombie_target = next.ash;
        int min_distance = dist;

        for (size_t j = 0; j < next.human_count; j++) {
            if (next.humans[j].dead)
                continue;
            dist = distance(next.zombies[i].pos, next.humans[j].pos);

            if (dist < min_distance) {
                min_distance = dist;
                zombie_target = next.humans[j].pos;
            }
        }
        next.zombies[i].pos = move(next.zombies[i].pos, zombie_target, 400);
    }

    // move ash
    next.ash = move(s->ash, target, 1000);

    // kill zombies
    for (size_t i = 0; i < next.zombie_count; i++) {
        if (next.zombies[i].dead)
            continue;
        if (distance(next.ash, next.zombies[i].pos) <= 2000) {
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
            if (distance(next.zombies[i].pos, next.humans[j].pos) < 400) {
                next.humans[j].dead = true;
                next.zombies[i].pos = next.humans[j].pos;
            }
        }
    }

    // update eval
    next.eval = evaluate(&next, s->eval);

    return next;
}

Point move(const Point from, const Point to, const int limit) {
    double dist = distance(from, to);

    if (dist <= limit || dist == 0) {
        return to;
    } else {
        int dx = to.x - from.x;
        int dy = to.y - from.y;

       return (Point){
           floor(from.x + dx * limit / dist),
           floor(from.y + dy * limit / dist),
        };
    }
}

double evaluate(const State *s, const double parent_eval) {
    double points = parent_eval;
    int deads = 0;

    for (size_t i = 0; i < s->zombie_count; i++) {
        if (distance(s->ash, s->zombies[i].pos) <= 2000)
            deads++;
    }

    int zombie_score = 0;

    for (size_t i = 0; i < s->human_count; i++) {
        if (s->humans[i].dead)
            continue;
        zombie_score += 10;
    }

    for (size_t i = 0; i < deads; i++) {
        points += zombie_score * FIB[i];
    }

    return points;
}

State clone_state(const State *s) {
    State new;

    new.ash = s->ash;

    new.human_count = s->human_count;
    memcpy(new.humans, s->humans, s->human_count * sizeof(Human));

    new.zombie_count = s->zombie_count;
    memcpy(new.zombies, s->zombies, s->zombie_count * sizeof(Zombie));

    new.eval = s->eval;

    return new;
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
    else
        return 0;
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
}

void print_state(const State *s) {
    fprintf(stderr, "[DEBUG] Ash = (%d, %d)\n", s->ash.x, s->ash.y);

    fprintf(stderr, "[DEBUG] human_count = %zu\n", s->human_count);
    print_humans(s->humans);

    fprintf(stderr, "[DEBUG] zombie_count = %zu\n", s->zombie_count);
    print_zombies(s->zombies);

    fprintf(stderr, "[DEBUG] Eval = %.2f\n", s->eval);
}
