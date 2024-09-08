#include <algorithm>
#include <iostream>
#include <vector>

bool is_even(int n) {
    return n % 2 == 0;
}

int main() {
    std::vector<int> vec = {2, 4, 6, 1, 3, 5};

    auto it = std::partition_point(vec.begin(), vec.end(), is_even);

    std::cout << "Partition point: " << std::distance(vec.begin(), it) << std::endl;

    return 0;
}