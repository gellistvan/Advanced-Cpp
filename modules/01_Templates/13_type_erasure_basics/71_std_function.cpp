#include <functional>
#include <any>
#include <iostream>
#include <string>

void std_any_example() {
    std::any value = 42;
    std::cout << std::any_cast<int>(value) << std::endl; // Output: 42

    value = std::string("Hello, World!");
    std::cout << std::any_cast<std::string>(value) << std::endl; // Output: Hello, World!

    try {
        std::cout << std::any_cast<int>(value) << std::endl; // Throws std::bad_any_cast
    } catch (const std::bad_any_cast& e) {
        std::cout << "Bad any cast: " << e.what() << std::endl; // Output: Bad any cast: bad any cast
    }
}


void printMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void std_function_example() {
    std::function<void(const std::string&)> func = printMessage;
    func("Hello, World!"); // Output: Hello, World!

    func = [](const std::string& message) {
        std::cout << "Lambda: " << message << std::endl;
    };
    func("Hello, Lambda!"); // Output: Lambda: Hello, Lambda!
}

int main() {
    std_any_example();
    std_function_example();
    return 0;
}