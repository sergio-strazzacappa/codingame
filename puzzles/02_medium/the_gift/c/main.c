#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;          // number of participants
int c;          // price of the gift
int *budgets;   // list of budgets of the participants 

void init();
void solve();
int cmp(const void *a, const void *b);
void clean();
void debug();

int main() {
    init();
    solve();
    debug();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &n, &c);

    budgets = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        scanf("%d", &budgets[i]);
}

void solve() {
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += budgets[i];

    if (sum < c)
        // not enough budget to buy the present
        printf("IMPOSSIBLE\n");
    else {
        int contributions[n];

        for (int i = 0; i < n; i++)
            contributions[i] = 0;

        while (c > 0) {
            int average;

            if (c >= n)
                average = c / n;
            else
                average = ceil((float)c / (float)n);

            for (int i = 0; i < n; i++) {
                if (budgets[i] == 0)
                    continue;
                if (c < average)
                    continue;
                if (budgets[i] <= average) {
                    contributions[i] += budgets[i];
                    c -= budgets[i];
                    budgets[i] = 0;
                } else {
                    contributions[i] += average;
                    c -= average;
                    budgets[i] -= average;
                }
            }
        }

        // sort the solution in ascending order
        qsort(contributions, n, sizeof(contributions[0]), cmp);

        for (int i = 0; i < n; i++)
            printf("%d\n", contributions[i]);
    }
}

int cmp(const void *a, const void *b) {
    return *(int *)a > *(int *)b;
}

void clean() {
    free(budgets);
}

void debug() {
    fprintf(stderr, "[DEBUG] List of budgets: [");

    for (int i = 0; i < n; i++)
        fprintf(stderr, " %d", budgets[i]);

    fprintf(stderr, " ]\n");
}
