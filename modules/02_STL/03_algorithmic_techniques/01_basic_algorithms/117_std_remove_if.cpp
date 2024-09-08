#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 2, 5};

    // Remove all instances of 2
    auto new_end = std::remove(vec.begin(), vec.end(), 2);
    vec.erase(new_end, vec.end());

    std::cout << "Vector after remove: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    // Remove all even numbers
    vec = {1, 2, 3, 4, 2, 5};
    new_end = std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    vec.erase(new_end, vec.end());

    std::cout << "Vector after remove_if: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}