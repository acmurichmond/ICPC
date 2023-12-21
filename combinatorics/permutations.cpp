// Permutations
// C++
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void find_permutations(std::vector<T> &vec) {
    std::sort(vec.begin(), vec.end());
    do {
        for (const auto &item : vec) {
            std::cout << item << ' ';
        }
        std::cout << '\n';
    } while (std::next_permutation(vec.begin(), vec.end()));
}

int main() {
    std::vector<int> items = {1, 2, 3}; // Replace with your iterable
    find_permutations(items);
    return 0;
}