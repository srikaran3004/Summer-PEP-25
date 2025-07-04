#include <iostream>

const int MOD = 1e9+7;

int multiply(int a, int b) {
    return (1LL * a * b) % MOD;
}

int power(int base, int exponent) {
    int result = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent & 1)
            result = multiply(result, base);
        exponent >>= 1;
        base = multiply(base, base);
    }
    return result;
}

int modInverse(int x) {
    return power(x, MOD - 2);
}

int divide(int a, int b) {
    return multiply(a, modInverse(b));
}

int add(int a, int b) {
    return (a + b) % MOD;
}

int subtract(int a, int b) {
    return (a - b + MOD) % MOD;
}

int main() {
    int a = 12345;
    int b = 67890;
    
    std::cout << "Addition: " << add(a, b) << std::endl;
    std::cout << "Subtraction: " << subtract(a, b) << std::endl;
    std::cout << "Multiplication: " << multiply(a, b) << std::endl;
    std::cout << "Power a^b mod MOD: " << power(a, b) << std::endl;
    
    int inv = modInverse(a);
    std::cout << "Modular inverse of a: " << inv << std::endl;
    std::cout << "Division (b/a): " << divide(b, a) << std::endl;
    
    return 0;
}
