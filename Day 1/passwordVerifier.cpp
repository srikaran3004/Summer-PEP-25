#include <iostream>
#include <string>
#include <functional>

using namespace std;

bool regexMatch(const string& text, const string& pat) {
    function<bool(size_t,size_t)> rec = [&](size_t i, size_t j) -> bool {
        if (j == pat.size()) return i == text.size();

        bool star = (j + 1 < pat.size() && pat[j + 1] == '*');

        if (!star) {
            if (i == text.size()) return false;
            if (pat[j] != '.' && pat[j] != text[i]) return false;
            return rec(i + 1, j + 1);
        }

        if (rec(i, j + 2)) return true;          // zero-occurrence branch
        while (i < text.size() && (pat[j] == '.' || pat[j] == text[i])) {
            ++i;                                 // consume one char
            if (rec(i, j + 2)) return true;      // try the rest
        }
        return false;
    };
    return rec(0, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string pattern, text;
    cout << "Enter regex pattern   : ";
    getline(cin, pattern);
    cout << "Enter string to test : ";
    getline(cin, text);

    if (text.size() < 8) {
        cout << "Rejected: input string length (" << text.size()
             << ") is < 8 characters.\n";
        return 0;
    }

    cout << (regexMatch(text, pattern) ? "MATCH" : "NO MATCH") << '\n';
    return 0;
}
