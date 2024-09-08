#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination(source.size());

    std::transform(source.begin(), source.end(), destination.begin(), [](int x) { return x * x; });

    std::cout << "Source vector: ";
    for (const auto& val : source) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    std::cout << "Transformed vector: ";
    for (const auto& val : destination) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}