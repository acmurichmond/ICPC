// Prime Factorization
// C++
#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> primeFactors(int n) {
    std::vector<int> primes;
    while (n % 2 == 0) {
        primes.push_back(2);
        n = n / 2;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            primes.push_back(i);
            n = n / i;
        }
    }
    if (n > 2) {
        primes.push_back(n);
    }
    return primes;
}