// nCr (n choose r)
// C++
#include <iostream>
long long factorial(int n) {
    long long result = 1;
    for(int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
long long nCr(int n, int r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}

int main() {
    int n, r;
    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << "Enter r: ";
    std::cin >> r;

    if(n < r || n < 0 || r < 0) {
        std::cout << "Invalid input! n and r must be non-negative, and n must be greater than or equal to r." << std::endl;
    } else {
        std::cout << "The number of combinations (nCr) for n=" << n << " and r=" << r << " is: " << nCr(n, r) << std::endl;
    }

    return 0;
}
