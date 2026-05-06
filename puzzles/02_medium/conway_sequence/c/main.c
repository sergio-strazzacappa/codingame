#include <stdio.h>

#define SIZE 10000

int R;
int L;
int seq[SIZE];
int seq_index;

void init();
void solve();
void copy(int seq[], int current_seq[], int current_seq_index);
void debug(int seq[], int index, int level);

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%d%d", &R, &L);
    seq_index = 0;
    seq[seq_index++] = R;
}

void solve() {
    int current_line = 2;

    while (current_line <= L) {
        int current_seq[SIZE];
        int current_seq_index = 0;

        int rep = 0;
        int prev_elem;
        for (int i = 0; i < seq_index; i++) {
            // iterate over the previous line
            int elem = seq[i];

            if (rep == 0) {
                prev_elem = elem;
                rep++;
                continue;
            }

            if (elem == prev_elem) {
                rep++;
            } else {
                current_seq[current_seq_index++] = rep;
                current_seq[current_seq_index++] = prev_elem;
                rep = 0;
                i--;
            }
        }
        current_seq[current_seq_index++] = rep;
        current_seq[current_seq_index++] = seq[seq_index - 1];
        copy(seq, current_seq, current_seq_index);
        current_line++;
    }

    for (int i = 0; i < seq_index; i++) {
        printf("%d", seq[i]);

        if (i == seq_index - 1)
            printf("\n");
        else
            printf(" ");
    }
}

void copy(int seq[], int current_seq[], int current_seq_index) {
    for (int i = 0; i < current_seq_index; i++)
        seq[i] = current_seq[i];
    seq_index = current_seq_index;
}

void debug(int seq[], int index, int level) {
    fprintf(stderr, "[DEBUG] level = %d [", level);
    for (int i = 0; i < index; i++)
        fprintf(stderr, " %d", seq[i]);
    fprintf(stderr, " ]\n");
}
