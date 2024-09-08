#include <iostream>
#include <tuple>

int main() {
    std::tuple<int, double, std::string> t = std::make_tuple(1, 3.14, "hello");

    auto [i, d, s] = t; // Unpack the tuple

    std::cout << "Integer: " << i << std::endl;
    std::cout << "Double: " << d << std::endl;
    std::cout << "String: " << s << std::endl;

    // Access by type
    auto& d2 = std::get<double>(t);
    d2 = 2.71;

    std::cout << "Updated tuple: (" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")" << std::endl;

    return 0;
}