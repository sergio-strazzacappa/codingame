#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#define NUM_BOWLS 7

void debug(const size_t my_bowls[], const size_t op_bowls[]) {
    fprintf(stderr, "Opp: [");

    for (size_t i = 0; i < NUM_BOWLS; i++) {
        fprintf(stderr, "%zu", op_bowls[i]);

        if (i < NUM_BOWLS - 1)
            fprintf(stderr, ", ");
    }

    fprintf(stderr, "]\n");
    fprintf(stderr, "Me: [");

    for (size_t i = 0; i < NUM_BOWLS; i++) {
        fprintf(stderr, "%zu", my_bowls[i]);

        if (i < NUM_BOWLS - 1)
            fprintf(stderr, ", ");
    }

    fprintf(stderr, "]\n");
}

void solve(size_t my_bowls[], size_t op_bowls[], size_t num) {
    size_t grains = my_bowls[num];
    bool me = true;
    bool replay = false;

    my_bowls[num] = 0;

    if (num == 6) {
        me = false;
        num = 0;
    } else {
        num++;
    }

    while (grains > 0) {
        if (me) {
            // iterate over my bowls
            // from 0 to 6
            my_bowls[num]++;

            if (num == 6) {
                // change to opp bowls
                replay = true;
                num = 0;
                me = false;
            } else {
                replay = false;
                num++;
            }
        } else {
            // iterate over my opp bowls
            // from 0 to 5
            op_bowls[num]++;

            if (num == 5) {
                // change to my bowls
                num = 0;
                me = true;
            } else {
                num++;
            }
            replay = false;
        }
        grains--;
    }

    // print the result
    for (size_t i = 0; i < NUM_BOWLS - 1; i++)
        printf("%zu ", op_bowls[i]);

    printf("[%zu]\n", op_bowls[NUM_BOWLS - 1]);

    for (size_t i = 0; i < NUM_BOWLS - 1; i++)
        printf("%zu ", my_bowls[i]);

    printf("[%zu]\n", my_bowls[NUM_BOWLS - 1]);

    if (replay)
        printf("REPLAY\n");
}

int main(void) {
    size_t my_bowls[NUM_BOWLS], op_bowls[NUM_BOWLS], num;

    char line[101];

    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';

    char *token = strtok(line, " ");

    size_t index = 0;
    while (token != NULL) {
        op_bowls[index++] = atoi(token);
        token = strtok(NULL, " ");
    }

    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';

    token = strtok(line, " ");

    index = 0;
    while (token != NULL) {
        my_bowls[index++] = atoi(token);
        token = strtok(NULL, " ");
    }

    scanf("%zu", &num);

    solve(my_bowls, op_bowls, num);

    return EXIT_SUCCESS;
}
