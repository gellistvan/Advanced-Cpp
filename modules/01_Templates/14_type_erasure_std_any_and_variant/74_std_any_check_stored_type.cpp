#include <any>
#include <iostream>
#include <typeinfo>

int main() {
    std::any value = 42;

    if (value.type() == typeid(int)) {
        std::cout << "The stored type is int" << std::endl;
    } else {
        std::cout << "The stored type is not int" << std::endl;
    }

    value = std::string("Hello, World!");

    if (value.type() == typeid(std::string)) {
        std::cout << "The stored type is std::string" << std::endl;
    } else {
        std::cout << "The stored type is not std::string" << std::endl;
    }

    return 0;
}