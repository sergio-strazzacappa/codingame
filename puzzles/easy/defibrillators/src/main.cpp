#include <bits/stdc++.h>

using namespace std;

struct User {
    double lon;
    double lat;
} user;

struct defib {
    int id;
    string name;
    string address;
    string phone_number;
    double lon;
    double lat;
};

void solve(int n, defib defibs[]) {
    double min_d = INT32_MAX;
    string min_name = "";

    for (int i = 0; i < n; i++) {
        double x =
            (defibs[i].lon - user.lon) * cos((user.lat + defibs[i].lat) / 2);
        double y = defibs[i].lat - user.lat;
        double d = sqrt(pow(x, 2) + pow(y, 2)) * 6371;

        if (d < min_d) {
            min_d = d;
            min_name = defibs[i].name;
        }
    }

    cout << min_name << endl;
}

double deg_to_rad(string s) {
    int coma = s.find(',');

    if (coma != string::npos) {
        s.replace(coma, 1, ".");
    }

    return stod(s);
}

int main() {
    string lon, lat;

    cin >> lon;
    cin.ignore();

    cin >> lat;
    cin.ignore();

    user.lon = deg_to_rad(lon);
    user.lat = deg_to_rad(lat);

    int n;
    cin >> n;
    cin.ignore();

    defib defibs[n];

    for (int i = 0; i < n; i++) {
        string defib;
        getline(cin, defib);

        string fields[] = { "", "", "", "", "", "" };
        int field_number = 0;

        for (int j = 0; j < defib.size(); j++) {
            if (defib[j] == ';') {
                field_number++;
                continue;
            }
            fields[field_number] += defib[j];
        }

        defibs[i].id = stoi(fields[0]);
        defibs[i].name = fields[1];
        defibs[i].address = fields[2];
        defibs[i].phone_number = fields[3];
        defibs[i].lon = deg_to_rad(fields[4]);
        defibs[i].lat = deg_to_rad(fields[5]);
    }
    solve(n, defibs);
}
