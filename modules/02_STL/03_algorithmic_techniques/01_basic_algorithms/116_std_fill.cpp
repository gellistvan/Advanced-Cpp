#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec(5);

    std::fill(vec.begin(), vec.end(), 7);

    std::cout << "Filled vector: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}