#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 20

struct node {
    bool generic;
    int *digit;
    struct node *childs[10];
};

int n;
struct node *root;

void init();
void add(struct node *n, char telephone[]);
int size(struct node *n);
void clean();

int main() {
    init();

    for (int i = 0; i < n; i++) {
        char telephone[LENGTH + 1];
        scanf("%s", telephone);

        add(root, telephone);
    }

    printf("%d\n", size(root));

    return 0;
}

void init() {
    scanf("%d", &n);

    root = (struct node *)malloc(sizeof(struct node));
    root->generic = true;
    root->digit = NULL;

    for (int i = 0; i < 10; i++)
        root->childs[i] = NULL;
}

void add(struct node *n, char telephone[]) {
    if (!strlen(telephone))
        return;

    int digit = telephone[0] - '0';

    for (int i = 0; i < strlen(telephone); i++)
        telephone[i] = telephone[i + 1];

    if (n->childs[digit] == NULL) {
        // add a new child
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->generic = false;

        new_node->digit = (int *)malloc(sizeof(int));
        *(new_node->digit) = digit;

        for (int i = 0; i < 10; i++)
            new_node->childs[i] = NULL;

        n->childs[digit] = (struct node *)malloc(sizeof(struct node));
        n->childs[digit] = new_node;
    }
    add(n->childs[digit], telephone);
}

int size(struct node *n) {
    int s = 1;

    if (n->generic)
        s = 0;

    for (int i = 0; i < 10; i++) {
        if (n->childs[i] != NULL) {
            s += size(n->childs[i]);
        }
    }
    return s;
}

void clean(struct node *n) {
    free(n->digit);
    for (int i = 0; i < 10; i++) {
        if (n->childs[i] != NULL) {
            clean(n->childs[i]);
        }
    }
    free(n);
}
