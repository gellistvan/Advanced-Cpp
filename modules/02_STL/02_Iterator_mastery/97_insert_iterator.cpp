#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination1;
    std::deque<int> destination2;

    std::copy(source.begin(), source.end(), std::back_inserter(destination1));
    std::copy(source.begin(), source.end(), std::front_inserter(destination2));


    std::cout << "Destination vector 1: ";
    for (const auto& val : destination1) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    std::cout << "Destination vector 2: ";
    for (const auto& val : destination2) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}