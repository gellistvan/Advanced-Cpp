#include <iostream>
#include <type_traits>

// Function enabled only for integral types
template<typename T>
std::enable_if_t<std::is_integral_v<T>, void> print(T value) {
    std::cout << value << " is an integral type." << std::endl;
}

// Function enabled only for floating-point types
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, void> print(T value) {
    std::cout << value << " is a floating-point type." << std::endl;
}

int main() {
    print(42);     // Output: 42 is an integral type.
    print(3.14);   // Output: 3.14 is a floating-point type.
    // print("Hello"); // Compilation error: no matching function to call 'print'
    return 0;
}