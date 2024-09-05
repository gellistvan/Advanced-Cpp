#include <iostream>
#include <concepts>

// Define a concept for numeric types
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Template function using improved syntax
template<Numeric T, Numeric U>
auto add(T a, U b) {
    return a + b;
}

int main() {
    std::cout << add(3, 4.5) << std::endl; // Output: 7.5
    return 0;
}