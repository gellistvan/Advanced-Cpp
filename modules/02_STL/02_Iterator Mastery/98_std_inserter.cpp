#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination = {10, 20, 30};

    auto it = destination.begin();
    std::advance(it, 1); // Move iterator to the second position

    std::copy(source.begin(), source.end(), std::inserter(destination, it));

    std::cout << "Destination vector: ";
    for (const auto& val : destination) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}