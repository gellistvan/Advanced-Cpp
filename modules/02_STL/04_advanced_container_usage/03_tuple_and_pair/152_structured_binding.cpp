#include <iostream>
#include <utility>

int main() {
    std::pair<int, std::string> p(1, "one");

    auto [num, str] = p; // Unpack the pair

    std::cout << "Number: " << num << std::endl;
    std::cout << "String: " << str << std::endl;

    return 0;
}