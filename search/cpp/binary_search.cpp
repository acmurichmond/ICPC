// Binary Search 
// C++
#include <iostream>
#include <vector>

template <typename T>
int binarySearch(const std::vector<T>& arr, const T& target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}




int main() {
    // example (strings):
    // std::vector<std::string> stringArray = {"apple", "banana", "cherry", "date", "elderberry"};
    // std::cout << "Testing with string array: ";
    // std::cout << "Index of 'date': " << binarySearch(stringArray, std::string("date")) << std::endl;
    return 0;
}