#include <bits/stdc++.h>
using namespace std;

long long digit_sum(long long x)
{
    long long s = 0;
    while (x) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;                
    cin >> t;
    while (t--) {
        long long n;              
        cin >> n;
        while (__gcd(n, digit_sum(n)) == 1)
            ++n;
        cout << n << '\n';
    }
    return 0;
}
