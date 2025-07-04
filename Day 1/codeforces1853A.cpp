#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;  
    cin >> T;
    while (T--) {
        int n;  
        cin >> n;
        vector<ll> a(n);
        for (ll &x : a) cin >> x;

        bool notSorted = false;
        for (int i = 1; i < n && !notSorted; ++i)
            if (a[i - 1] > a[i]) notSorted = true;

        if (notSorted) {
            cout << 0 << '\n';
            continue;
        }

        ll d_min = LLONG_MAX;
        for (int i = 1; i < n; ++i)
            d_min = min(d_min, a[i] - a[i - 1]);

        cout << (d_min / 2 + 1) << '\n';
    }
    return 0;
}
