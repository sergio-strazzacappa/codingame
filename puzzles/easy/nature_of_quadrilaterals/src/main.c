#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

typedef enum q_type_e {
    NOTHING,
    PARALLELOGRAM,
    RHOMBUS,
    RECTANGLE,
    SQUARE
} q_type_t;

typedef struct point_s {
    char id;
    int x;
    int y;
} point_t;

// is a parallelogram if both opposite sides are parallel to each other
bool is_parallelogram(point_t a, point_t b, point_t c, point_t d) {
    int abx = b.x - a.x;
    int aby = b.y - a.y;

    int bcx = c.x - b.x;
    int bcy = c.y - b.y;

    int cdx = d.x - c.x;
    int cdy = d.y - c.y;

    int dax = a.x - d.x;
    int day = a.y - d.y;

    // ab | cd
    if (abx * cdy - aby * cdx != 0)
        return false;

    // bc | da
    if (bcx * day - bcy * dax != 0)
        return false;

    return true;
}

// is a rhombus if the 4 side's length are equal
bool is_rhombus(point_t a, point_t b, point_t c, point_t d) {
    int ab = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
    int bc = pow(b.x - c.x ,2) + pow(b.y - c.y, 2);
    int cd = pow(c.x - d.x ,2) + pow(c.y - d.y, 2);
    int da = pow(d.x - a.x ,2) + pow(d.y - a.y, 2);

    return ab == bc && bc == cd && cd == da;
}

// is a rectangle if the 4 angles are right
bool is_rectangle(point_t a, point_t b, point_t c, point_t d) {
    int abx = b.x - a.x;
    int aby = b.y - a.y;

    int bcx = c.x - b.x;
    int bcy = c.y - b.y;

    int cdx = d.x - c.x;
    int cdy = d.y - c.y;

    int dax = a.x - d.x;
    int day = a.y - d.y;

    // AB -> BC
    if (abx * bcx + aby * bcy != 0)
        return false;

    // BC -> CD
    if (bcx * cdx + bcy * cdy != 0)
        return false;

    // CD -> DA
    if (cdx * dax + cdy * day != 0)
        return false;

    // If 3 angles are right, the fourth must be right
    return true;
}

q_type_t solve(point_t a, point_t b, point_t c, point_t d) {
    if (is_rectangle(a, b, c, d) && is_rhombus(a, b, c, d))
        return SQUARE;

    if (is_rectangle(a, b, c, d))
        return RECTANGLE;

    if (is_rhombus(a, b, c, d))
        return RHOMBUS;

    if (is_parallelogram(a, b, c, d))
        return PARALLELOGRAM;

    return NOTHING;
}

int main(void) {
    int n;
    scanf("%d\n", &n);

    for (size_t i = 0; i < n; i++) {
        point_t a = {0};
        point_t b = {0};
        point_t c = {0};
        point_t d = {0};
        char buffer[32];

        if (fgets(buffer, sizeof(buffer), stdin)) {
            sscanf(buffer, "%c %d %d %c %d %d %c %d %d %c %d %d",
                    &a.id, &a.x, &a.y,
                    &b.id, &b.x, &b.y,
                    &c.id, &c.x, &c.y,
                    &d.id, &d.x, &d.y
            );
        }

        q_type_t t = solve(a, b, c, d);

        switch (t) {
            case PARALLELOGRAM:
                printf("%c%c%c%c is a parallelogram.\n", a.id, b.id, c.id, d.id);
                break;
            case RHOMBUS:
                printf("%c%c%c%c is a rhombus.\n", a.id, b.id, c.id, d.id);
                break;
            case RECTANGLE:
                printf("%c%c%c%c is a rectangle.\n", a.id, b.id, c.id, d.id);
                break;
            case SQUARE:
                printf("%c%c%c%c is a square.\n", a.id, b.id, c.id, d.id);
                break;
            default:
                printf("%c%c%c%c is a quadrilateral.\n", a.id, b.id, c.id, d.id);
                break;
       }
    }
    return EXIT_SUCCESS;
}
