#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000

struct node {
    int x;
    int y;
};

int n;
struct node *nodes;
int nodes_index;

void init();
void solve();
struct node *next(int y);
void clean();
void debug();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d", &n);
    nodes = (struct node *)malloc(sizeof(struct node) * n);
    nodes_index = 0;

    for (int i = 0; i < n; i++) {
        int x;
        int y;
        scanf("%d%d", &x, &y);

        nodes[nodes_index++] = (struct node){x, y};
    }
}

void solve() {
    int longest = 0;

    for (int i = 0; i < nodes_index; i++) {
        struct node *start = &nodes[i];
        int current = 1;

        while (start != NULL) {
            current++;
            start = next(start->y);
        }
        if (current > longest)
            longest = current;
    }
    printf("%d\n", longest);
}

struct node *next(int y) {
    struct node *n = NULL;
    for (int i = 0; i < nodes_index; i++) {
        if (nodes[i].x == y) {
            n = &nodes[i];
            return n;
        }
    }
    return n;
}

void clean() {
    free(nodes);
}

void debug() {
    for (int i = 0; i < nodes_index; i++)
        fprintf(stderr, "[%d -> %d]\n", nodes[i].x, nodes[i].y);
}
