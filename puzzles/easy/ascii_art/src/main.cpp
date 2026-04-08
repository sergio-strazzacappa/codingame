// 1. Descomponer el string t en cada caracter
// 2. Para cada caracter: recorrer la representación ascii. Cada letra = width

#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve() {
    int l, h;
    string t;

    cin >> l;
    cin.ignore();
    cin >> h;
    cin.ignore();
    getline(cin, t);

    string representation[h];

    for (int i = 0; i < h; i++) {
        string row;
        getline(cin, row);
        representation[i] = row;
    }

    for (int i = 0; i < h; i++) {
        cerr << representation[i] << endl;
    }

    for (int i = 0; i < h; i++) {
        int starting_index = 0;
        for (char j : t) {
            char c = j;

            if (c >= 'a' && c <= 'z') {
                c = toupper(j);
            }

            if (c >= 'A' && c <= 'Z') {
                starting_index = l * (c - 65);
            } else {
                starting_index = l * ('Z' + 1 - 65);
            }
            cout << representation[i].substr(starting_index, l);

        }
        cout << endl;
    }
}

int main() {
    solve();
}
