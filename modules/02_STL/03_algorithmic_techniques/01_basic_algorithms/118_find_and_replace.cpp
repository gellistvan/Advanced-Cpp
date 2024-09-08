#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 2};

    // Find the first occurrence of 2
    auto it = std::find(vec.begin(), vec.end(), 2);
    if (it != vec.end()) {
        // Replace it with 9
        *it = 9;
    }

    std::cout << "Vector after find and replace: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}