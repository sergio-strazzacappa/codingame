#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define BASE_DMG 10

enum Type {
    FIGHTER,
    CRUISER
};

typedef struct alien {
    enum Type ship;
    int hp;
    int armor;
    int damage;
    bool destroyed;
} Alien;

int turn = 0;
int my_shield = 5000;
int n;
Alien *aliens;

void solve();
void receive_dmg();
int attack(int alien);
int turn_damage(Alien a);
bool test_win();
void print_aliens();

int main() {
    scanf("%d", &n);

    aliens = (Alien *)malloc(sizeof(Alien) * n);

    for (int i = 0; i < n; i++) {
        char ship[8];
        int hp;
        int armor;
        int damage;

        scanf("%s%d%d%d", ship, &hp, &armor, &damage);

        Alien a;

        if (strcmp(ship, "FIGHTER") == 0)
            a.ship = FIGHTER;
        else
            a.ship = CRUISER;

        a.hp = hp;
        a.armor = armor;
        a.damage = damage;
        a.destroyed = false;

        aliens[i] = a;
    }

    solve();
    free(aliens);

    return 0;
}

void solve() {
    int alien = -1;

    while (1) {
        turn++;
        fprintf(stderr, "[DEBUG] It's turn %d\n", turn);

        print_aliens();
        receive_dmg();
        alien = attack(alien);

        if (my_shield < 0) {
            printf("FLEE\n");
            break;
        }

        if (test_win()) {
            printf("%d\n", my_shield);
            break;
        }
    }
}

void receive_dmg() {
    int dmg_received = 0;
    for (int i = 0; i < n; i++) {
        if (aliens[i].destroyed)
            continue;
        dmg_received += aliens[i].damage;
    }
    my_shield -= dmg_received;

    fprintf(stderr, "[DEBUG] Damage received: %d\n", dmg_received);
    fprintf(stderr, "[DEBUG] Shields: %d\n", my_shield);
}

int attack(int alien) {
    int best_alien = 0;
    float biggest_dmg = 0;
 
    // there's an alien beeing attacked
    // continue attacking it
    if (alien > 0)
        best_alien = alien;

    // search the best target
    for (int i = 0; i < n && alien < 0; i++) {
        Alien a = aliens[i];

        if (a.destroyed)
            continue;

        int dmg = turn_damage(a);
        int turns_to_destroy = ceil((float)a.hp / dmg);
        float dmg_received = 1 / (float)turns_to_destroy * a.damage;

        if (dmg_received > biggest_dmg) {
            biggest_dmg = dmg_received;
            best_alien = i;
        }

        fprintf(stderr, "[DEBUG] Alien %d receives %d dmg in a turn, ", i, dmg);
        fprintf(stderr, "will be destroy in %d turns, ", turns_to_destroy);
        fprintf(stderr, "dmg received by this alien is %f\n", dmg_received);
    }

    // attack the alien
    fprintf(stderr, "[DEBUG] Attack the alien %d\n", best_alien);

    int dmg = turn_damage(aliens[best_alien]);
    
    aliens[best_alien].hp -= dmg;

    if (aliens[best_alien].hp <= 0) {
        aliens[best_alien].destroyed = true;
        return -1;
    }

    return best_alien;
}

// returns the damage that alien a deals in a turn
int turn_damage(Alien a) {
    int turn_dmg = BASE_DMG;

    if (a.ship == FIGHTER)
        turn_dmg *= 2;

    turn_dmg -= a.armor;

    if (turn_dmg <= 0)
        turn_dmg = 1;
    
    return turn_dmg;
}

// test if every alien is destroyed to end the game
bool test_win() {
    for (int i = 0; i < n; i++) {
        if (!aliens[i].destroyed)
            return false;
    }
    return true;
}

void print_aliens() {
    fprintf(stderr, "[DEBUG] There are %d aliens:\n", n);

    for (int i = 0; i < n; i++) {
        Alien a = aliens[i];
        fprintf(stderr, "[DEBUG] [ class: %s, hp: %d, armor: %d, dmg: %d ]\n",
            !a.ship ? "FIGHTER" : "CRUISER", a.hp, a.armor, a.damage);

        if (a.destroyed) {
            fprintf(stderr, "[DEBUG] This alien is destroyed\n");
        }
    }
}
