#include <iostream>

// Consteval function for compile-time validation (C++20)
consteval int validate_positive(int n) {
    if (n <= 0) {
        throw "Value must be positive";
    }
    return n;
}

int main() {
    constexpr int value = validate_positive(10);
    std::cout << "Validated value: " << value << std::endl; // Output: 10

    // constexpr int invalid_value = validate_positive(-5); // Error: Value must be positive
    return 0;
}