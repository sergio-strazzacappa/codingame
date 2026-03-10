#include <bits/stdc++.h>

using namespace std;

string to_binary(char c) {
    string binary = "";

    while (c != 0) {
        int bit = c % 2;
        c = c / 2;

        binary = to_string(bit) + binary;
    }

    for (int i = binary.size(); i < 7; i++) {
        binary = "0" + binary;
    }
    return binary;
}

void solve() {
    string message;
    string binary = "";
    getline(cin, message);

    for (char c : message) {
        binary += to_binary(c);
    }

    cerr << "Binary message: " << binary << endl;

    string first_block = "";
    string second_block = "";
    int prev;
    int quantity;

    // for each char
    for (size_t i = 0; i < binary.size(); i++) {
        int bit = (int)binary[i] - 48; // bit 0, 1

        if (i == 0) {
            // first bit
            quantity = 1;
        } else {
            // rest
            if (bit == prev) {
                // consecutive bits
                quantity++;
            } else {
                // start again
                for (int j = 0; j < quantity; j++) {
                    second_block += "0";
                }

                cout << first_block << " " << second_block << " ";

                first_block = "";
                second_block = "";
                quantity = 1;
            }
        }

        prev = bit;

        if (first_block == "") {
            if (bit == 0) {
                first_block = "00";
            } else {
                first_block = "0";
            }
        }

        if (i == binary.size() - 1) {
            for (int j = 0; j < quantity; j++) {
                second_block += "0";
            }
            cout << first_block << " " << second_block;
        }
    }
}

int main() {
    solve();
}
