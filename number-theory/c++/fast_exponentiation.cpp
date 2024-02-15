// Fast Exponentiation 
// C++
// Does not work with negatives
#include <iostream>

long long optimize(long long val, int power) {
    long long result = 1;
    while (power > 0) {
        if (power % 2 == 1) {
            result = result * val;
        }
        power = power / 2;
        val = val * val;
    }
    return result;
}

int main() {
    long long cal = optimize(3, 6);
    std::cout << cal << std::endl;
    return 0;
}
