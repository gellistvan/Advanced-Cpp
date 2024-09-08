#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 2, 5, 2};

    // Count the number of 2s
    int count = std::count(vec.begin(), vec.end(), 2);
    std::cout << "Number of 2s: " << count << std::endl;

    // Remove all instances of 2
    auto new_end = std::remove(vec.begin(), vec.end(), 2);
    vec.erase(new_end, vec.end());

    std::cout << "Vector after remove: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}