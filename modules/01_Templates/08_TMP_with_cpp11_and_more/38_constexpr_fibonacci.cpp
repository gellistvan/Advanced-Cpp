#include <iostream>

// Constexpr function with if statements (C++17)
constexpr int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    constexpr int result = fibonacci(10);
    std::cout << "Fibonacci of 10 is " << result << std::endl; // Output: 55
    return 0;
}