// Fermat Primality Test
// C++
#include <iostream>
#include <random>
#include <ctime>
long long modular_pow(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

bool is_prime(long long n, int iterations = 10) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<long long> distr(2, n - 2);

    for (int i = 0; i < iterations; i++) {
        long long a = distr(eng);
        if (modular_pow(a, n - 1, n) != 1) {
            return false;
        }
    }
    return true;
}

int main() {
    long long number_to_test = 19; // Replace with the number you want to test
    int iterations = 5; // Replace with the number of iterations for the test

    if (is_prime(number_to_test, iterations)) {
        std::cout << number_to_test << " is prime.\n";
    } else {
        std::cout << number_to_test << " is not prime.\n";
    }

    return 0;
}
