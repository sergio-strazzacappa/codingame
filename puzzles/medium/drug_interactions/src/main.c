#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_N 100

bool MATRIX[MAX_N][MAX_N];

// return true of drugs a and b have a bad interaction (at least 3 common
// letters)
bool bad_interaction(const char a[], const char b[]) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t common = 0;
    bool used[len_b];

    memset(used, 0, sizeof(used));

    for (size_t i = 0; i < len_a; i++) {
        for (size_t j = 0; j < len_b; j++) {
            if (!used[j] && toupper(a[i]) == toupper(b[j])) {
                common++;
                if (common == 3)
                    return true;
                used[j] = true;
                break;
            }
        }
    }
    return false;
}

void BK(const size_t n, const bool R[], bool P[], bool X[], size_t *max_found) {
    // check if P and X are both empty
    bool P_empty = true;
    bool X_empty = true;

    for (size_t i = 0; i < n; i++) {
        if (P[i])
            P_empty = false;
        if (X[i])
            X_empty = false;
        if (!P_empty && !X_empty)
            break;
    }

    if (P_empty && X_empty) {
        size_t current = 0;

        for (size_t i = 0; i < n; i++) {
            if (R[i])
                current++;
        }

        if (current > *max_found)
            *max_found = current;

        return;
    }

    // Backgracking

    // choose a pivot with max degree
    int u = -1;
    size_t max_degree = 0;

    for (size_t i = 0; i < n; i++) {
        if (P[i] || X[i]) {
            size_t count = 0;
            for (size_t j = 0; j < n; j++) {
                if (MATRIX[i][j])
                    count++;
            }

            if (count > max_degree) {
                max_degree = count;
                u = i;
            }
        }
    }

    // call BK for every node v in P - N(u)
    for (size_t i = 0; i < n; i++) {
        if (P[i] && !MATRIX[u][i]) {
            bool NP[n], NX[n], NR[n];

            memcpy(NR, R, n * sizeof(bool));
            NR[i] = true;

            for (size_t j = 0; j < n; j++) {
                NP[j] = P[j] && MATRIX[i][j];
                NX[j] = X[j] && MATRIX[i][j];
            }

            BK(n, NR, NP, NX, max_found);

            P[i] = false;
            X[i] = true;
        }
    }
}

void solve(const size_t n) {
    bool R[n], P[n], X[n];
    size_t max = 0;

    memset(R, false, sizeof(R));
    memset(P, true, sizeof(P));
    memset(X, false, sizeof(X));

    BK(n, R, P, X, &max);

    printf("%zu\n", max);
}

int main(void) {
    size_t n;
    scanf("%zu", &n);
    fgetc(stdin);

    char drugs[MAX_N][1025];
    for (size_t i = 0; i < n; i++) {
        fgets(drugs[i], sizeof(drugs[i]), stdin);
        drugs[i][strcspn(drugs[i], "\n")] = '\0';
    }

    // initialize the matrix
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (bad_interaction(drugs[i], drugs[j])) {
                MATRIX[i][j] = false;
                MATRIX[j][i] = false;
            } else {
                MATRIX[i][j] = true;
                MATRIX[j][i] = true;
            }
        }
    }

    solve(n);

    return EXIT_SUCCESS;
}
