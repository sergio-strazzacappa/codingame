#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct point_s {
    int x;
    int y;
} point_t;

typedef struct line_s {
    int a;
    int b;
    int c;
} line_t;

void solve(line_t lines[], size_t n, point_t p, point_t q) {
    bool same_color = true;
    for (size_t i = 0; i < n; i++) {
        /*
         * replace the points in both equations, if the result is zero then
         * its on the line, if the signs are different then the color changes
         */
        line_t l = lines[i];
        int ecuation_a = l.a * p.x + l.b * p.y + l.c;
        int ecuation_b = l.a * q.x + l.b * q.y + l.c;

        if (ecuation_a == 0 || ecuation_b == 0) {
            printf("ON A LINE\n");
            return;
        } else if ((ecuation_a < 0 && ecuation_b > 0) || (ecuation_a > 0 && ecuation_b < 0)) {
            same_color = !same_color;
        }
    }

    if (same_color)
        printf("YES\n");
    else
        printf("NO\n");
}

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void normalize(line_t *l) {
    int common = gcd(l->a, gcd(l->b, l->c));

    if (common == 0)
        return;

    // simplification
    l->a /= common;
    l->b /= common;
    l->c /= common;

    // normalize the sign
    if (l->a < 0) {
        l->a = -l->a;
        l->b = -l->b;
        l->c = -l->c;
    } else if (l->a == 0 && l->b < 0) {
        l->b = -l->b;
        l->c = -l->c;
    }
}

int main(void) {
    point_t p, q;
    scanf("%d%d%d%d", &p.x, &p.y, &q.x, &q.y);

    line_t lines[128];
    size_t n;
    scanf("%zu", &n);

    size_t capacity = 0;
    for (size_t i = 0; i < n; i++) {
        bool found = false;
        line_t l;
        scanf("%d%d%d", &l.a, &l.b, &l.c);

        normalize(&l);

        for (size_t j = 0; j < capacity; j++) {
            // don't store the line of it is already stored
            if (lines[j].a == l.a && lines[j].b == l.b && lines[j].c == l.c)
                found = true;
        }

        if (!found)
            lines[capacity++] = l;
    }

    solve(lines, capacity, p, q);

    return EXIT_SUCCESS;
}
