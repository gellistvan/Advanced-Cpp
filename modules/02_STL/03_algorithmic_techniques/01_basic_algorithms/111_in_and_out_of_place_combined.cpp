#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> intermediate(source.size());

    // Out-of-place transformation
    std::transform(source.begin(), source.end(), intermediate.begin(), [](int x) { return x * x; });

    // In-place modification
    std::for_each(intermediate.begin(), intermediate.end(), [](int& x) { x += 10; });

    std::cout << "Source vector: ";
    for (const auto& val : source) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    std::cout << "Processed vector: ";
    for (const auto& val : intermediate) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}