#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void solve(int score) {
    for (size_t tries = 0; tries * 5 <= score; tries++) {
        int trie_sum = tries * 5;
        for (size_t trans = 0; trans <= tries && trie_sum + trans * 2 <= score; trans++) {
            int trans_sum = trie_sum + trans * 2;
            if ((score - trans_sum) % 3 == 0) {
                printf("%zu %zu %d\n", tries, trans, (score - trans_sum) / 3);
            }
        }
    }
}

int main(void) {
    int score;
    scanf("%d", &score);

    solve(score);

    return EXIT_SUCCESS;
}
