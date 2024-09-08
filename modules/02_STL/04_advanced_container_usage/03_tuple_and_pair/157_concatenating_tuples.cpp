#include <iostream>
#include <tuple>

int main() {
    std::tuple<int, double> t1 = std::make_tuple(1, 3.14);
    std::tuple<std::string, char> t2 = std::make_tuple("hello", 'A');

    auto t3 = std::tuple_cat(t1, t2);

    std::cout << "Concatenated tuple: ("
              << std::get<0>(t3) << ", "
              << std::get<1>(t3) << ", "
              << std::get<2>(t3) << ", "
              << std::get<3>(t3) << ")" << std::endl;

    return 0;
}