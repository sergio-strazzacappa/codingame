#include <stdio.h>
#include <stdbool.h>

#define SIZE 8

char board[SIZE][SIZE];

void init();
void solve();
bool backtracking(bool queen_rows[]);
bool status();
void print_board();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    for (int y = 0; y < SIZE; y++) {
        char row[9];
        scanf("%s", row);

        for (int x = 0; x < SIZE; x++) {
            board[y][x] = row[x];
        }
    }
}

void solve() {
    bool queen_rows[SIZE];

    for (int i = 0; i < SIZE; i++)
        queen_rows[i] = false;

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (board[y][x] == 'Q') {
                queen_rows[y] = true;
            }
        }
    }

    bool solution = backtracking(queen_rows);

    if (solution)
        print_board();
    else
        fprintf(stderr, "[ERROR] Solution not found\n");
}

bool backtracking(bool queen_rows[]) {
    if (!status(board))
        return false;

    for (int y = 0; y < SIZE; y++) {
        if (!queen_rows[y]) {
            for (int x = 0; x < SIZE; x++) {
                board[y][x] = 'Q';
                queen_rows[y] = true;
                bool solution = backtracking(queen_rows);

                if (solution)
                    return true;

                board[y][x] = '.';
                queen_rows[y] = false;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if (!queen_rows[i])
            return false;
    }
    return true;
}

// returns true if the board is correct, false otherwise
bool status(char board[SIZE][SIZE]) {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (board[y][x] != 'Q')
                continue;

            for (int i = 0; i < SIZE; i++) {
                // check row
                if (i != x && board[y][i] == 'Q') {
                    return false;
                }

                // check column
                if (i != y && board[i][x] == 'Q') {
                    return false;
                }

                // check diagonal
                int index = i + 1;
                if (y - index >= 0 && x - index >= 0) {
                    if (board[y - index][x - index] == 'Q') {
                        return false;
                    }
                } else if (y + index < SIZE && x + index < SIZE){
                    if (board[y + index][x + index] == 'Q') {
                        return false;
                    }
                }

                if (y - index >= 0 && x + index < SIZE) {
                    if (board[y - index][x + index] == 'Q') {
                        return false;
                    }
                } else if (y + index < SIZE && x - index >= 0) {
                    if (board[y + index][x - index] == 'Q') {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void print_board() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            printf("%c", board[y][x]);
        }
        printf("\n");
    }
}
