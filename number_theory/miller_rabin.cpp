// Miller Rabin Primality Test
// C++
#include <iostream>
#include <random>

// Modular exponentiation
int modPow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

bool isPrime(int n, int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, n - 2);

    for (int i = 0; i < k; i++) {
        int a = dis(gen);
        int x = modPow(a, d, n);
        if (x == 1 || x == n - 1)
            continue;

        while (d != n - 1) {
            x = modPow(x, 2, n);
            d *= 2;

            if (x == 1) return false;
            if (x == n - 1) break;
        }

        if (d != n - 1) return false;
    }

    return true;
}

int main() {
    int num, k;
    std::cout << "Enter a number to check for primality: ";
    std::cin >> num;
    std::cout << "Enter the number of iterations: ";
    std::cin >> k;

    if (isPrime(num, k))
        std::cout << num << " is probably prime." << std::endl;
    else
        std::cout << num << " is not prime." << std::endl;

    return 0;
}
