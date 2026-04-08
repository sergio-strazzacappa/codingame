#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef enum call_e {
    NONE,
    EVEN,
    ODD,
    PLAIN
} call_t;

int play_round(int cash, char play[]) {
    // substract the current bet
    int bet = ceil(cash / 4.);
    cash -= bet;

    // parse the input: BALL CALL [NUMBER]
    int ball = -1;
    call_t call = NONE;
    int number = -1;
    char *token = strtok(play, " ");

    while (token != NULL) {
        if (ball == -1)
            ball = atoi(token);
        else if (call == NONE) {
            switch (token[0]) {
                case 'E':
                    call = EVEN;
                    break;
                case 'O':
                    call = ODD;
                    break;
                case 'P':
                    call = PLAIN;
                    break;
                default:
                    fprintf(stderr, "[ERROR] Incorrect call\n");
                    break;
            }
        } else
            number = atoi(token);
        token = strtok(NULL, " ");
    }

    // calculate the cash
    switch (call) {
        case EVEN:
            if (ball != 0 && ball % 2 == 0)
                bet *= 2;
            else
                bet = 0;
            break;
        case ODD:
            if (ball % 2 == 1)
                bet *= 2;
            else
                bet = 0;
            break;
        case PLAIN:
            if (number == ball)
                bet *= 36;
            else
                bet = 0;
            break;
        default:
            fprintf(stderr, "[ERROR] Incorrect call\n");
    }

    return cash + bet;
}

void solve(int rounds, int cash) {
    for (size_t i = 0; i < rounds; i++) {
        char play[1025];
        scanf("%[^\n]", play);
        fgetc(stdin);

        cash = play_round(cash, play);
    }

    printf("%d\n", cash);
}

int main(void) {
    int rounds, cash;
    scanf("%d%d", &rounds, &cash);
    fgetc(stdin);

    solve(rounds, cash);

    return EXIT_SUCCESS;
}
