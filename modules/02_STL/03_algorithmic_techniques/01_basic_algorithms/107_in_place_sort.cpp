#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {4, 2, 5, 1, 3};

    std::sort(vec.begin(), vec.end());

    std::cout << "Sorted vector: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}