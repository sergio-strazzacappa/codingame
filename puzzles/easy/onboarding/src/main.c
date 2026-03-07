#include <stdio.h>
#include <stdlib.h>

int main () {
    while (1) {
        char enemy_1[257], enemy_2[257];
        int dist_1, dist_2;

        scanf("%s%d%s%d", enemy_1, &dist_1, enemy_2, &dist_2);

        if (dist_1 < dist_2)
            printf("%s\n", enemy_1);
        else
            printf("%s\n", enemy_2);
    }

    return EXIT_SUCCESS;
}
