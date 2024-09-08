#include <iostream>
#include <vector>
#include <array>

int main() {
    std::vector<std::array<int, 3>> vec;
    vec.reserve(3);

    vec.push_back({1, 2, 3});
    vec.push_back({4, 5, 6});
    vec.push_back({7, 8, 9});

    for (const auto& arr : vec) {
        for (const auto& elem : arr) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}