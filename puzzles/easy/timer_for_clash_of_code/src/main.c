#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct ts_s {
    size_t min;
    size_t sec;
} ts_t;

void solve(ts_t *stop, ts_t player, size_t n, int *last_sec, bool *start) {
    int seconds = player.min * 60 + player.sec;
    int stop_sec = seconds - (float)256 / (float)pow(2, n);

    if (n == 6) {
        printf("%1zu:%02zu\n", player.min, player.sec);
        *start = true;
        return;
    }

    if (seconds < *last_sec) {
        printf("%1zu:%02zu\n", stop->min, stop->sec);
        *start = true;
        return;
    }

    if (stop_sec < 0)
        stop_sec = 0;

    stop->min = stop_sec / 60;
    stop->sec = stop_sec % 60;

    *last_sec = stop_sec;
}

int main(void) {
    ts_t stop = {0, 0};
    size_t n;
    scanf("%zu", &n);
    fgetc(stdin);

    if (n == 0) {
        printf("NO GAME\n");

        return EXIT_SUCCESS;
    }

    int last_sec = 0;
    bool start = false;
    for (size_t i = 0; i < n; i++) {
        char min[16], sec[16];

        // read the minutes
        fgets(min, 3, stdin);
        min[strcspn(min, ":")] = '\0';

        // read the seconds
        fgets(sec, 4, stdin);
        sec[strcspn(sec, "\n")] = '\0';

        ts_t player = {atoi(min), atoi(sec)};
        solve(&stop, player, i, &last_sec, &start);

        if (start)
            break;
    }

    if (!start)
        printf("%1zu:%02zu\n", stop.min, stop.sec);

    return EXIT_SUCCESS;
}
