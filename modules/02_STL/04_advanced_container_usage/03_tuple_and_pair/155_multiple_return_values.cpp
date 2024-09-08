#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> get_values() {
    return std::make_tuple(1, 3.14, "hello");
}

int main() {
    auto [i, d, s] = get_values();

    std::cout << "Integer: " << i << std::endl;
    std::cout << "Double: " << d << std::endl;
    std::cout << "String: " << s << std::endl;

    return 0;
}