#include <bits/stdc++.h>

using namespace std;

void solve(int light_x, int light_y, int initial_tx, int initial_ty) {
    while (true) {
        int remaining_turns;
        string direction = "";

        cin >> remaining_turns;
        cin.ignore();

        if (initial_ty > light_y) {
            direction += "N";
            initial_ty--;
        } else if (initial_ty < light_y) {
            direction += "S";
            initial_ty++;
        }
        if (initial_tx > light_x) {
            direction += "W";
            initial_tx--;
        } else if (initial_tx < light_x) {
            direction += "E";
            initial_tx++;
        }
        cout << direction << endl;
    }
}

int main() {
    int light_x, light_y, initial_tx, initial_ty;

    cin >> light_x;
    cin.ignore();

    cin >> light_y;
    cin.ignore();

    cin >> initial_tx;
    cin.ignore();

    cin >> initial_ty;
    cin.ignore();

    solve(light_x, light_y, initial_tx, initial_ty);
}
