#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int closest_temp = INT32_MAX;

    cin >> n;
    cin.ignore();

    if (!n) {
        closest_temp = 0;
    } else {
        while (n--) {
            int temp;

            cin >> temp;
            cin.ignore();

            if (abs(temp) < abs(closest_temp)) {
                closest_temp = temp;
            } else if (abs(temp) == abs(closest_temp)) {
                if (temp > 0) {
                    closest_temp = temp;
                }
            }
        }
    }
    cout << closest_temp << endl;

    return EXIT_SUCCESS;
}
