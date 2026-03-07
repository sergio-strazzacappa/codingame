#include <bits/stdc++.h>

using namespace std;

int main() {
    string enemy_1, enemy_2;
    int dist_1, dist_2;

    while (1) {
        cin >> enemy_1;
        cin.ignore();
        cin >> dist_1;
        cin.ignore();
        cin >> enemy_2;
        cin.ignore();
        cin >> dist_2;
        cin.ignore();

        if (dist_1 < dist_2)
            cout << enemy_1 << endl;
        else
            cout << enemy_2 << endl;
    }

    return 0;
}
