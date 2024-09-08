#include <iostream>
#include <tuple>

int main() {
    // Using make_tuple
    std::tuple<int, double, std::string> t1 = std::make_tuple(1, 3.14, "hello");

    // Direct initialization
    std::tuple<int, double, std::string> t2(2, 2.71, "world");

    // Accessing elements
    std::cout << "t1: (" << std::get<0>(t1) << ", " << std::get<1>(t1) << ", " << std::get<2>(t1) << ")" << std::endl;
    std::cout << "t2: (" << std::get<0>(t2) << ", " << std::get<1>(t2) << ", " << std::get<2>(t2) << ")" << std::endl;

    return 0;
}