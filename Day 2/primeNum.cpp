#include <iostream>
#include <vector>
using namespace std;

bool IsPrime(int num) {
    if (num <= 1) {
        return false;
    }
    if (num <= 3) {
        return true;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return false;
    }
    
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void printPrimesUpToN(int n) {
    cout << n;
    for (int i = 2; i <= n; i++) {
        if (IsPrime(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    
    printPrimesUpToN(n);
    
    return 0;
}

/*
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
const int N = 10000;

void brute() {
    for (int n = 2; n <= N; ++n)
        for (int d = 2; d < n; ++d)
            if (n % d == 0) break;
}

void sqrt_check() {
    for (int n = 2; n <= N; ++n)
        for (int d = 2; d * d <= n; ++d)
            if (n % d == 0) break;
}

int main() {
    clock_t t1 = clock();
    brute();
    clock_t t2 = clock();
    sqrt_check();
    clock_t t3 = clock();
    cout<<t1<<" "<<t2<<endl;
    double time1 = double(t2 - t1) / CLOCKS_PER_SEC;
    double time2 = double(t3 - t2) / CLOCKS_PER_SEC;

    cout << (time1 - time2) << '\n';
    return 0;
}

*/