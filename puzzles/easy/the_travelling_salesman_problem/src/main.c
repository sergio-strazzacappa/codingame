#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

typedef struct point_s {
    int id;
    int x;
    int y;
    bool visited;
} point_t;

double distance(point_t p, point_t q) {
    return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
}

void solve(point_t cities[], size_t n) {
    assert(n > 0);

    size_t current = 0;
    size_t next = 0;
    cities[current].visited = true;
    double total_distance = 0;

    while (true) {
        double closest = INT_MAX;
        bool found = false;

        for (size_t i = 0; i < n; i++) {
            if (cities[current].id == cities[i].id)
                continue;
            if (cities[i].visited)
                continue;

            double d = distance(cities[current], cities[i]);

            if (d < closest) {
                found = true;
                closest = d;
                next = i;
            }
        }

        if (!found) {
            total_distance += distance(cities[current], cities[0]);
            break;
        }

        total_distance += closest;
        cities[next].visited = true;
        current = next;
    }

    printf("%.0f\n", round(total_distance));
}

int main(void) {
    size_t n;
    scanf("%zu", &n);

    point_t cities[32];
    for (size_t i = 0; i < n; i++) {
        point_t p;
        p.id = i;
        p.visited = false;
        scanf("%d%d", &p.x, &p.y);
        cities[i] = p;
    }

    solve(cities, n);

    return EXIT_SUCCESS;
}
