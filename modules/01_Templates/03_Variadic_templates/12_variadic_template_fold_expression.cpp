#include <iostream>

// Variadic sum function using fold expression
template<typename... Args>
auto sum(Args... args) {
    return (args + ...); // Fold expression
}

int main() {
    std::cout << "Sum: " << sum(1, 2, 3, 4, 5) << std::endl; // Output: Sum: 15
    std::cout << "Sum: " << sum(1.1, 2.2, 3.3) << std::endl; // Output: Sum: 6.6
    return 0;
}