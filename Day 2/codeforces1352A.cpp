#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        string s;
        cin >> s;

        vector<int> ans;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            if (s[i] != '0') {
                int digit = s[i] - '0';
                int power = 1;
                for (int j = 0; j < n - i - 1; ++j)
                    power *= 10;
                ans.push_back(digit * power);
            }
        }

        cout << ans.size() << '\n';
        for (int x : ans) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
