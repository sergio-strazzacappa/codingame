#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct lander {
    int x;
    int y;
    int v_speed;
    int h_speed;
    int fuel;
    int rotate;
    int power;
};

void init() {
    int surface_n;

    cin >> surface_n;
    cin.ignore();

    for (int i = 0; i < surface_n; i++) {
        int land_x;
        int land_y;

        cin >> land_x >> land_y;
        cin.ignore();
    }
}

void read_input(lander &mars_lander) {
    cin >> mars_lander.x >> mars_lander.y >> mars_lander.h_speed;
    cin >> mars_lander.v_speed >> mars_lander.fuel >> mars_lander.rotate;
    cin  >> mars_lander.power;
    cin.ignore();
}

void solve(lander mars_lander) {
    int power;
    if (mars_lander.v_speed <= -35) {
        power = 4;
    } else {
        power = 0;
    }
    cout << "0 " << power << endl;
}

int main() {
    init();

    lander mars_lander;

    while (1) {
        read_input(mars_lander);
        solve(mars_lander);
    }
}
