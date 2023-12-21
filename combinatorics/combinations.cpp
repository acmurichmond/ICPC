// Generating Combinations
// C++
#include <iostream>
#include <vector>

template<typename T>
void print_combination(const std::vector<T>& vec, const std::vector<bool>& select) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (select[i]) {
            std::cout << vec[i] << " ";
        }
    }
    std::cout << std::endl;
}
template<typename T>
void find_combinations(std::vector<T> vec, int combination_length) {
    std::vector<bool> select(vec.size(), false);
    std::fill(select.begin(), select.begin() + combination_length, true);
    do {
        print_combination(vec, select);
    } while (std::prev_permutation(select.begin(), select.end()));
}

int main() {
    std::vector<int> items = {1, 2, 3, 4}; // Replace with your iterable
    int combination_length = 2; // Replace with the desired combination length

    find_combinations(items, combination_length);
    return 0;
}
