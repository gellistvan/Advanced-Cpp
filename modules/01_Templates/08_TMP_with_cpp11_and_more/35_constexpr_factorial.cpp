#include <iostream>

// Constexpr function for compile-time factorial calculation
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

constexpr int factorial2(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    constexpr int result = factorial(5);
    std::cout << "Factorial of 5 is " << result << std::endl; // Output: 120
    return 0;
}