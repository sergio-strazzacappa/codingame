#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();

    vector<int> horses;

    for (int i = 0; i < n; i++) {
        int pi;
        cin >> pi;
        cin.ignore();
        horses.push_back(pi);
    }

    sort(horses.begin(), horses.end());

    int closest = INT32_MAX;

    for (int i = 0; i < n - 1; i++) {
        int dif = horses[i + 1] - horses[i];

        if (dif < closest) {
            closest = dif;
        }
    }
    cout << closest << endl;
}
