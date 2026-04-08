#include <stdio.h>
#include <stdlib.h>

#define MAX_V_SPEED 39

typedef struct spaceship_s {
    int x;
    int y;
    int h_speed;
    int v_speed;
    int fuel;
    int rotate;
    int power;
} spaceship_t;

void solve(void) {
    spaceship_t mars_lander;

    while (1) {
        scanf("%d%d%d%d%d%d%d",
            &mars_lander.x, &mars_lander.y, &mars_lander.h_speed,
            &mars_lander.v_speed, &mars_lander.fuel, &mars_lander.rotate,
            &mars_lander.power);

        if (mars_lander.v_speed < -(MAX_V_SPEED))
            mars_lander.power = 4;
        else
            mars_lander.power = 0;

        printf("0 %d\n", mars_lander.power);
    }
}

int main(void) {
    int surface_n;
    scanf("%d", &surface_n);

    for (size_t i = 0; i < surface_n; i++) {
        // omit for the 1st level
        int land_x;
        int land_y;
        scanf("%d%d", &land_x, &land_y);
    }

    solve();

    return EXIT_SUCCESS;
}
