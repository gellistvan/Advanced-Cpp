#include <algorithm>
#include <iostream>
#include <vector>

bool is_even(int n) {
    return n % 2 == 0;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::stable_partition(vec.begin(), vec.end(), is_even);

    std::cout << "Stable partitioned vector: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}