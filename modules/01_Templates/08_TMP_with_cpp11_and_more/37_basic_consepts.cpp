#include <iostream>
#include <concepts>

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

// Function enabled only for integral types
void process(Integral auto value) {
    std::cout << value << " is an integral type." << std::endl;
}

// Function enabled only for floating-point types
void process(FloatingPoint auto value) {
    std::cout << value << " is a floating-point type." << std::endl;
}

int main() {
    process(42);       // Output: 42 is an integral type.
    process(3.14);     // Output: 3.14 is a floating-point type.
    // process("text"); // Compilation error: no matching function to call 'process'
    return 0;
}