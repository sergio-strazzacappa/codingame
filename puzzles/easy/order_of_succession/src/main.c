#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef struct people_s {
    char name[41];
    char parent[41];
    int birth;
    char death[5];
    char religion[11];
    char gender[2];
} people_t;

typedef struct node_s {
    people_t p;
    struct node_s *first_child;
    struct node_s *next;
} node_t;

node_t *root;

void DFS(node_t *n) {
    if (n == NULL)
        return;

    if (strcmp(n->p.death, "-") == 0 && strcmp(n->p.religion, "Catholic") != 0)
        printf("%s\n", n->p.name);

    DFS(n->first_child);
    DFS(n->next);
}

node_t *search_parent(node_t *n, people_t p) {
    if (n == NULL)
        return NULL;

    if (strcmp(n->p.name, p.parent) == 0)
        return n;

    node_t *parent = search_parent(n->first_child, p);

    if (parent != NULL)
        return parent;

    return search_parent(n->next, p);
}

int insert_node(node_t *parent, people_t p) {
    // create the node
    node_t *new = (node_t *)malloc(sizeof(node_t));
    new->p = p;
    new->first_child = NULL;
    new->next = NULL;

    // the list of childen is empty
    if (parent->first_child == NULL) {
        parent->first_child = new;

        return EXIT_SUCCESS;
    }

    node_t *node = parent->first_child;
    node_t *prev = NULL;

    while (node != NULL) {
        bool same_gender = node->p.gender[0] == new->p.gender[0];

        if ((node->p.gender[0] == 'F' && new->p.gender[0] == 'M') ||
            (same_gender && new->p.birth < node->p.birth)) {

            // insert the node at first position
            if (prev == NULL) {
                parent->first_child = new;
                new->next = node;

                return EXIT_SUCCESS;
            }

            // insert the node at the middle
            node_t *temp = node;
            prev->next = new;
            new->next = temp;

            return EXIT_SUCCESS;
        }

        prev = node;
        node = node->next;
    }

    // insert the node at the end
    if (node == NULL && prev != NULL) {
        prev->next = new;

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int add_node(node_t **n, people_t p) {
    node_t *parent = search_parent(*n, p);

    // parent not found, set the root
    if (parent == NULL) {
        root = (node_t *)malloc(sizeof(node_t));
        root->p = p;
        root->first_child = NULL;
        root->next = NULL;

        return EXIT_SUCCESS;
    }

    return insert_node(parent, p);
}

void free_node(node_t *n) {
    if (n == NULL)
        return;

    free_node(n->first_child);
    free_node(n->next);

    free(n);
}

void print_node(node_t *n) {
    if (n == NULL)
        return;

    fprintf(stderr, "%p = [ %s, %s ] %p %p\n",
            n, n->p.name, n->p.parent, n->first_child, n->next);

    print_node(n->first_child);
    print_node(n->next);
}

int main(void) {
    size_t n;
    scanf("%zu", &n);

    root = NULL;
    for (size_t i = 0; i < n; i++) {
        people_t p;
        scanf("%s%s%d%s%s%s", p.name, p.parent, &p.birth, p.death, p.religion, p.gender);

        add_node(&root, p);
    }

    print_node(root);

    DFS(root);
    free_node(root);

    return EXIT_SUCCESS;
}
