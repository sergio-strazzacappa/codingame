#include <iostream>

#define COND1 (format[format_index] == '?' && text_index < text.size())
#define COND2 (format[format_index] == text[text_index])

using namespace std;

string solve(string text, int text_index, string format, int format_index) {
    string verdict = "";

    while (format_index < format.size() && verdict != "MATCH") {
        if (format[format_index] == '~' && text[text_index] != '~') {
            for (int i = 0; i < text.size() - text_index && verdict != "MATCH"; i++) {
                verdict = solve(text, text_index + i, format, format_index + 1);
            }
            format_index++;
        } else if (COND1 || COND2) {
            text_index++;
            format_index++;
        } else {
            verdict = "FAIL";
            break;
        }
    }

    if (format_index == format.size()) {
        verdict = "MATCH";
    }

    return verdict;
}

int main() {
    string text;
    getline(cin, text);
    string format;
    getline(cin, format);

    cout << solve(text, 0, format, 0) << endl;
}