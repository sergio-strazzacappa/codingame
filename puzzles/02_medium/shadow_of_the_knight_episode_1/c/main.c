#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct point {
    int x;
    int y;
} Point;

int rows;
int cols;
int turns;
Point me;

void init();
void solve();
void debug(char bomb_dir[]);

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%d%d%d%d%d", &cols, &rows, &turns, &me.x, &me.y);
}

void solve() {
    int x_range[2] = {0, cols - 1};
    int y_range[2] = {0, rows - 1};
    Point move = {0, 0};

    while (1) {
        char bomb_dir[4];
        scanf("%s", bomb_dir);

        if (strcmp(bomb_dir, "U") == 0) {
            y_range[1] = me.y;
            move.x = me.x;
            move.y = (y_range[1] + y_range[0]) / 2.0; 
        } else if (strcmp(bomb_dir, "UR") == 0) {
            x_range[0] = me.x; 
            y_range[1] = me.y;
            move.x = ceil((x_range[1] + x_range[0]) / 2.0);
            move.y = (y_range[1] + y_range[0]) / 2; 
        } else if (strcmp(bomb_dir, "R") == 0) {
            x_range[0] = me.x;
            move.x = ceil((x_range[1] + x_range[0]) / 2.0);
            move.y = me.y;
        } else if (strcmp(bomb_dir, "DR") == 0) {
            x_range[0] = me.x;
            y_range[0] = me.y;
            move.x = ceil((x_range[1] + x_range[0]) / 2.0);
            move.y = ceil((y_range[1] + y_range[0]) / 2.0); 
        } else if (strcmp(bomb_dir, "D") == 0) {
            y_range[0] = me.y;
            move.x = me.x;
            move.y = ceil((y_range[1] + y_range[0]) / 2.0); 
        } else if (strcmp(bomb_dir, "DL") == 0) {
            x_range[1] = me.x;
            y_range[0] = me.y;
            move.x = (x_range[1] + x_range[0]) / 2;
            move.y = ceil((y_range[1] + y_range[0]) / 2.0); 
        } else if (strcmp(bomb_dir, "L") == 0) {
            x_range[1] = me.x;
            move.x = (x_range[1] + x_range[0]) / 2;
            move.y = me.y; 
        } else if (strcmp(bomb_dir, "UL") == 0) {
            x_range[1] = me.x;
            y_range[1] = me.y;
            move.x = (x_range[1] + x_range[0]) / 2;
            move.y = (y_range[1] + y_range[0]) / 2; 
        } else {
            fprintf(stderr, "[ERROR] Incorrect Bomb's Position\n");
        }

        me.x = move.x;
        me.y = move.y;

        printf("%d %d\n", move.x, move.y);
    }
}

void debug(char bomb_dir[]) {
    fprintf(stderr, "[DEBUG] Size of the map: %dX%d\n", rows, cols);
    fprintf(stderr, "[DEBUG] Number of turns remaining: %d\n", turns);
    fprintf(stderr, "[DEBUG] My position: (%d, %d)\n", me.x, me.y);
    fprintf(stderr, "[DEBUG] Bomb direction: %s\n", bomb_dir);
}
