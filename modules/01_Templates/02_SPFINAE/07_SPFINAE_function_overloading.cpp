#include <iostream>
#include <type_traits>

// Function enabled only for integral types
template<typename T>
std::enable_if_t<std::is_integral_v<T>, void> process(T value) {
    std::cout << value << " is an integral type." << std::endl;
}

// Function enabled only for floating-point types
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, void> process(T value) {
    std::cout << value << " is a floating-point type." << std::endl;
}

template<typename T>
std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>, void> is_signed(T value) {
    std::cout << value << " is a signed integral type." << std::endl;
}

int main() {
    process(42);       // Output: 42 is an integral type.
    process(3.14);     // Output: 3.14 is a floating-point type.
    // process("text"); // Error: no matching function to call 'process'

    is_signed(-42);      // Output: -42 is a signed integral type.

    return 0;
}
