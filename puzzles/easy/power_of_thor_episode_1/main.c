#include <stdio.h>

int main() {
    int light_x, light_y, initial_tx, initial_ty;
    scanf("%d%d%d%d", &light_x, &light_y, &initial_tx, &initial_ty);

    while (1) {
        int remianing_turns;
        scanf("%d", &remianing_turns);

        if (initial_ty < light_y) {
            printf("S");
            initial_ty++;
        }
        if (initial_ty > light_y) {
            printf("N");
            initial_ty--;
        }
        if (initial_tx < light_x) {
            printf("E");
            initial_tx++;
        }
        if (initial_tx > light_x) {
            printf("W");
            initial_tx--;
        }
        printf("\n");
    }
    return 0;
}