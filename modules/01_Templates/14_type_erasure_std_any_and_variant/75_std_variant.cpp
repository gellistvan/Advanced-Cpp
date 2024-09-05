#include <variant>
#include <iostream>
#include <string>

int main() {
    std::variant<int, std::string> value;

    // Store an int
    value = 42;
    std::cout << std::get<int>(value) << std::endl; // Output: 42

    // Store a string
    value = std::string("Hello, World!");
    std::cout << std::get<std::string>(value) << std::endl; // Output: Hello, World!

    // Attempt to retrieve a value of the wrong type
    try {
        std::cout << std::get<int>(value) << std::endl; // Throws std::bad_variant_access
    } catch (const std::bad_variant_access& e) {
        std::cout << "Bad variant access: " << e.what() << std::endl; // Output: Bad variant access: bad_variant_access
    }

    return 0;
}