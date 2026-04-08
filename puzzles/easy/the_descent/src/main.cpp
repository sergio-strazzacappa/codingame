#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve() {
    while (1) {
        int highest_index = 0;
        int highest_peak = 0;

        for (int i = 0; i < 8; i++) {
            int mountain_h;

            cin >> mountain_h;
            cin.ignore();

            if (mountain_h > highest_peak) {
                highest_peak = mountain_h;
                highest_index = i;
            }
        }
        cout << highest_index << endl;
    }
}

int main() {
    solve();
}
