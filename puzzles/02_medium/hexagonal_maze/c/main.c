#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct point {
    int x;
    int y;
} Point;

int cols;
int rows;
char **map;
int **distance;

const int even_directions[6][2] = {
    {1, 0},
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1}
};

const int odd_directions[6][2] = {
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, -1}
};

void init();
void solve();
void get_shortest_path(Point start, Point end);
void clean();
void print_map();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &cols, &rows);
    fgetc(stdin);

    map = (char **)malloc(sizeof(char *) * rows);
    distance = (int **)malloc(sizeof(int *) * rows);

    for (int y = 0; y < rows; y++) {
        map[y] = (char *)malloc(sizeof(char) * cols);
        distance[y] = (int *)malloc(sizeof(int) * cols);
        scanf("%[^\n]", map[y]);
        fgetc(stdin);

        for (int x = 0; x < cols; x++) {
            if (map[y][x] == '#')   distance[y][x] = -1;
            else                    distance[y][x] = 0;
        }
    }
}

void solve() {
    // get the start and end point
    Point *start = NULL;
    Point *end = NULL;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (map[y][x] == 'S') {
                start = (Point *)malloc(sizeof(Point));
                start->x = x;
                start->y = y;
            }
            if (map[y][x] == 'E') {
                end = (Point *)malloc(sizeof(Point));
                end->x = x;
                end->y = y;
            }
            if (start != NULL && end != NULL)
                break;
        }
    }

    Point q[cols * rows];
    int q_index = 0;
    bool done = false;

    q[q_index++] = *start;

    while (q_index > 0 && !done) { // start bfs
        // get the top of the queue and remove it
        Point current = q[0];

        for (int i = 1; i < q_index; i++) {
            q[i - 1] = q[i];
        }
        q_index--;

        for (int i = 0; i < 6; i++) {
            Point next;
            if (current.y % 2 == 0) { // even
                next.x = current.x + even_directions[i][0];
                next.y = current.y + even_directions[i][1];
            } else { // odd
                next.x = current.x + odd_directions[i][0];
                next.y = current.y + odd_directions[i][1];
            }

            if (next.x == cols)
                next.x = 0;
            if (next.x == -1)
                next.x = cols - 1;
            if (next.y == rows)
                next.y = 0;
            if (next.y == -1)
                next.y = rows - 1;
            
            if (map[next.y][next.x] == '#') {
                continue;
            }
            if (map[next.y][next.x] == 'E') {
                distance[next.y][next.x] = distance[current.y][current.x] + 1;
                get_shortest_path(*start, *end);
                done = true;
                break;
            }
            if (distance[next.y][next.x] > 0 || map[next.y][next.x] == 'S') {
                continue;
            }

            distance[next.y][next.x] = distance[current.y][current.x] + 1;
            q[q_index++] = next;
        }
    }

    free(start);
    free(end);
}

void get_shortest_path(Point start, Point end) {
    int d = distance[end.y][end.x];
    Point current = end;

    while (!(current.x == start.x && current.y == start.y)) {
        if (map[current.y][current.x] != 'E' && map[current.y][current.x] != 'S')
            map[current.y][current.x] = '.';

        for (int i = 0; i < 6; i++) {
            Point next;
            if (current.y % 2 == 0) { // even
                next.x = current.x + even_directions[i][0];
                next.y = current.y + even_directions[i][1];
            } else { // odd
                next.x = current.x + odd_directions[i][0];
                next.y = current.y + odd_directions[i][1];
            }

            if (next.x == cols)
                next.x = 0;
            if (next.x == -1)
                next.x = cols - 1;
            if (next.y == rows)
                next.y = 0;
            if (next.y == -1)
                next.y = rows - 1;

            if (distance[next.y][next.x] == d - 1) {
                current = next;
                break;
            }
        }
        d--;
        if (d == 0)
            break; // reach the start
    }

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

void clean() {
    for (int y = 0; y < rows; y++) {
        free(map[y]);
        free(distance[y]);
    }

    free(map);
    free(distance);
}

void print_map() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            fprintf(stderr, "%3d", distance[y][x]);
        }
        fprintf(stderr, "\n");
    }
}
