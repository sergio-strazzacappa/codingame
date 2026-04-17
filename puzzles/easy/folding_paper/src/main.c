#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

int solve(const char order[], const char side[]) {
    int folds[] = {1, 1, 1, 1}; // R/D/L/U
    int index;
    size_t len = strlen(order);

    for (size_t i = 0; i < len; i++) {
        switch (order[i]) {
            case 'R':
                folds[2] += folds[0];
                folds[0] =  1;
                folds[1] *= 2;
                folds[3] *= 2;
                break;
            case 'D':
                folds[3] += folds[1];
                folds[0] *= 2;
                folds[1] =  1;
                folds[2] *= 2;
                break;
            case 'L':
                folds[0] += folds[2];
                folds[1] *= 2;
                folds[2] =  1;
                folds[3] *= 2;
                break;
            case 'U':
                folds[1] += folds[3];
                folds[0] *= 2;
                folds[2] *= 2;
                folds[3] =  1;
                break;
            default:
                assert(0);
                break;
        }
    }

    switch (side[0]) {
        case 'R':
            index = 0;
            break;
        case 'D':
            index = 1;
            break;
        case 'L':
            index = 2;
            break;
        case 'U':
            index = 3;
            break;
        default:
            assert(0);
            break;
    }

    return folds[index];
}

int main(void) {
    char order[16];
    char side[16];

    fgets(order, sizeof(order), stdin);
    order[strcspn(order, "\n")] = '\0';

    fgets(side, sizeof(side), stdin);
    side[strcspn(side, "\n")] = '\0';

    int folds = solve(order, side);

    printf("%d\n", folds);

    return EXIT_SUCCESS;
}
