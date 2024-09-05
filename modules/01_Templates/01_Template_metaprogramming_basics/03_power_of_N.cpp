#include <iostream>

// General case
template<int Base, int Exponent>
struct Power {
    static constexpr int value = Base * Power<Base, Exponent - 1>::value;
};

// Specialization for base case
template<int Base>
struct Power<Base, 0> {
    static constexpr int value = 1;
};

int main() {
    constexpr int result = Power<2, 8>::value;
    std::cout << "2 to the power of 8 is " << result << std::endl; // Output: 256
    return 0;
}