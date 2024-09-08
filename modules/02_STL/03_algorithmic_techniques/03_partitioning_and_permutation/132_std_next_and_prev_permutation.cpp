#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3};

    do {
        for (const auto& val : vec) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    } while (std::next_permutation(vec.begin(), vec.end()));

    std::cout << "=====================" <<std::endl;
    vec = {3, 2, 1};

    do {
        for (const auto& val : vec) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    } while (std::prev_permutation(vec.begin(), vec.end()));

    return 0;
}