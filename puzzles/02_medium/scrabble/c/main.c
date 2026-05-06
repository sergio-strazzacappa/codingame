#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORD_SIZE 31

const int SCORES[26] = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4,
    10
};

int number_words;
char **words;       // dictionary
char letters[8];    // letters available

void init();
void solve();
bool is_correct(char *w);
int get_score(char *w);
void clean();
void debug();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%d", &number_words);
    fgetc(stdin);

    words = (char **)malloc(sizeof(char *) * number_words);

    for (int i = 0; i < number_words; i++) {
        char word[WORD_SIZE];
        scanf("%[^\n]", word);
        fgetc(stdin);

        words[i] = (char *)malloc(sizeof(char) * WORD_SIZE);
        strcpy(words[i], word);
    }

    scanf("%[^\n]", letters);
}

void solve() {
    // for every word in the dictionary check if it is possible to build it
    // using the available letters and calulate its score
    // keep the highest score and the corresponding index

    int max_score = 0;
    int index = 0;

    for (int i = 0; i < number_words; i++) {
        if (!is_correct(words[i]))
            continue;

        int score = get_score(words[i]);

        if (score > max_score) {
            max_score = score;
            index = i;
        }
    }

    printf("%s\n", words[index]);
}

// return true if the word w can be made with the avaliable letters
// false otherwise
bool is_correct(char *w) {
    bool used[8];

    for (int i = 0; i < 8; i++)
        used[i] = false;

    for (int i = 0; i < strlen(w); i++) {
        char c = w[i];
        bool found = false;

        for (int j = 0; j < 8; j++) {
            if (letters[j] == c && !used[j]) {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

// return the score of the word w
int get_score(char *w) {
    int score = 0;

    for (int i = 0; i < strlen(w); i++) {
        int pos = w[i] - 'a';
        score += SCORES[pos];
    }

    return score;
}

void clean() {
    for (int i = 0; i < number_words; i++)
        free(words[i]);
    free(words);
}

void debug() {
    fprintf(stderr, "[DEBUG] DICTIONARY\n");
    fprintf(stderr, "[DEBUG] ----------\n");

    for (int i = 0; i < number_words; i++)
        fprintf(stderr, "[DEBUG] %s\n", words[i]);

    fprintf(stderr, "[DEBUG] ----------\n");

    fprintf(stderr, "[DEBUG] Letters available: %s\n", letters);
}
