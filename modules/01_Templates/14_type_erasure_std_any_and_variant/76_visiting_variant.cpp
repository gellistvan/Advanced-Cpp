#include <variant>
#include <iostream>
#include <string>

int main() {
    std::variant<int, std::string> value;

    value = 42;

    std::visit([](auto&& arg) {
        std::cout << "Value: " << arg << std::endl;
    }, value); // Output: Value: 42

    value = std::string("Hello, World!");

    std::visit([](auto&& arg) {
        std::cout << "Value: " << arg << std::endl;
    }, value); // Output: Value: Hello, World!

    return 0;
}