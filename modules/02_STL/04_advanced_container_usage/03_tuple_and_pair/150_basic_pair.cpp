#include <iostream>
#include <utility>

int main() {
    // Using make_pair
    std::pair<int, std::string> p1 = std::make_pair(1, "one");

    // Direct initialization
    std::pair<int, std::string> p2(2, "two");

    std::cout << "p1: (" << p1.first << ", " << p1.second << ")" << std::endl;
    std::cout << "p2: (" << p2.first << ", " << p2.second << ")" << std::endl;

    return 0;
}
