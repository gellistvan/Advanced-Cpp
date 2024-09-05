#include <iostream>

// Base case: factorial of 0 is 1
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// Specialization for base case
template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

int main() {
    constexpr int result = Factorial<5>::value;
    std::cout << "Factorial of 5 is " << result << std::endl; // Output: 120
    return 0;
}