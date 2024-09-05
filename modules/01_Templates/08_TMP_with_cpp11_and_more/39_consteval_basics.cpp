#include <iostream>

// Consteval function for compile-time square calculation (C++20)
consteval int square(int n) {
    return n * n;
}

// Constexpr function for compile-time calculation of a polynomial
constexpr double polynomial(double x) {
    return 3 * x * x + 2 * x + 1;
}

int main() {
    constexpr int result = square(5);
    std::cout << "Square of 5 is " << result << std::endl; // Output: 25

    // int runtime_result = square(5); // Error: consteval function must be evaluated at compile time

    constexpr double result2 = polynomial(5.0);
    std::cout << "Polynomial(5.0) is " << result2 << std::endl; // Output: 86

    return 0;
}