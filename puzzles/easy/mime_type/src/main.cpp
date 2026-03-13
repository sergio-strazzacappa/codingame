#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, q;
    map<string, string> file_table;

    cin >> n;
    cin.ignore();
    cin >> q;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string ext, mt;
        cin >> ext >> mt;
        cin.ignore();

        transform(ext.begin(), ext.end(), ext.begin(), ::toupper);

        file_table.insert(pair<string, string>(ext, mt));
    }

    for (int i = 0; i < q; i++) {
        string fname;
        getline(cin, fname);

        int pos = fname.find_last_of('.');
        string ext;
        string output = "UNKNOWN\n";


        if (pos != string::npos) {
            ext = fname.substr(pos + 1, string::npos);
            transform(ext.begin(), ext.end(), ext.begin(), ::toupper);
        }

        map<string, string>::iterator it = file_table.find(ext);

        if (it != file_table.end()) {
            output = it->second + "\n";
        }

        cout << output;
    }
}
