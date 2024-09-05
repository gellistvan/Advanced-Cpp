#include <iostream>

// General case
template<int Base, int Exponent, bool IsEven = (Exponent % 2 == 0)>
struct Power {
    static constexpr int value = Base * Power<Base, Exponent - 1>::value;
};

// Specialization for even exponents
template<int Base, int Exponent>
struct Power<Base, Exponent, true> {
    static constexpr int value = Power<Base * Base, Exponent / 2>::value;
};

// Specialization for base case
template<int Base>
struct Power<Base, 0, true> {
    static constexpr int value = 1;
};

int main() {
    constexpr int result = Power<2, 8>::value;
    std::cout << "2 to the power of 8 is " << result << std::endl; // Output: 256
    return 0;
}