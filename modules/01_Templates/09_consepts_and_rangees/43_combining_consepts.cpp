#include <iostream>
#include <concepts>

// Define concepts for integral and floating-point types
template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

// Function template constrained by combined concepts
template<typename T>
requires Integral<T> || FloatingPoint<T>
T multiply(T a, T b) {
    return a * b;
}

int main() {
    std::cout << multiply(3, 4) << std::endl;       // Output: 12
    std::cout << multiply(3.14, 2.0) << std::endl;  // Output: 6.28
    // std::cout << multiply("Hello", "World") << std::endl; // Error: no matching function to call 'multiply'
    return 0;
}