#include <algorithm>
#include <iostream>
#include <vector>

bool is_even(int n) {
    return n % 2 == 0;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};

    auto partition_point = std::stable_partition(vec.begin(), vec.end(), is_even);

    std::cout << "Even elements permutations:" << std::endl;
    do {
        for (auto it = vec.begin(); it != partition_point; ++it) {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;
    } while (std::next_permutation(vec.begin(), partition_point));

    std::cout << "Odd elements permutations:" << std::endl;
    do {
        for (auto it = partition_point; it != vec.end(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;
    } while (std::next_permutation(partition_point, vec.end()));

    return 0;
}