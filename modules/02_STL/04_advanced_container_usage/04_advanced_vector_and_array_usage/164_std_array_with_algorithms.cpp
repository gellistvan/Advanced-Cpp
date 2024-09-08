#include <iostream>
#include <array>
#include <algorithm>

int main() {
    std::array<int, 5> arr = {5, 3, 4, 1, 2};

    std::sort(arr.begin(), arr.end());

    std::cout << "Sorted array: ";
    for (const auto& elem : arr) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    return 0;
}