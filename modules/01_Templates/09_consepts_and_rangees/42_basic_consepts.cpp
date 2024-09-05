#include <iostream>
#include <type_traits>

// Define a concept to check if a type is integral
template<typename T>
concept Integral = std::is_integral_v<T>;

// Function constrained by the Integral concept
void print_integral(Integral auto value) {
    std::cout << value << " is an integral type." << std::endl;
}

// Define a concept to check if a type is arithmetic
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// Function template constrained by the Arithmetic concept
template<Arithmetic T>
T add(T a, T b) {
    return a + b;
}

int main() {
    print_integral(42);   // Output: 42 is an integral type.
    // print_integral(3.14); // Error: no matching function to call 'print_integral'

    std::cout << add(3, 4) << std::endl;       // Output: 7
    std::cout << add(3.14, 2.86) << std::endl; // Output: 6
    // std::cout << add("Hello", "World") << std::endl; // Error: no matching function to call 'add'

    return 0;
}