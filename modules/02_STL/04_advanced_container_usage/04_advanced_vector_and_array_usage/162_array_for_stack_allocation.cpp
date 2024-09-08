#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    std::cout << "Array elements: ";
    for (const auto& elem : arr) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    return 0;
}