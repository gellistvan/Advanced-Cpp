#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::rotate(vec.begin(), vec.begin() + 2, vec.end());

    std::cout << "Rotated vector: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}