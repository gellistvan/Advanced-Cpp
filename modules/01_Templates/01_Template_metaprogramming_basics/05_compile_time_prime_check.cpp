#include <iostream>

// Primary template for checking divisibility
template<int N, int Divisor>
struct IsPrimeHelper {
    static constexpr bool value = (N % Divisor != 0) && IsPrimeHelper<N, Divisor - 1>::value;
};

// Specialization for base case when divisor is 1
template<int N>
struct IsPrimeHelper<N, 1> {
    static constexpr bool value = true;
};

// Primary template for checking primality
template<int N>
struct IsPrime {
    static constexpr bool value = IsPrimeHelper<N, N / 2>::value;
};

// Special cases for 0 and 1
template<>
struct IsPrime<0> {
    static constexpr bool value = false;
};

template<>
struct IsPrime<1> {
    static constexpr bool value = false;
};

int main() {
    constexpr bool result = IsPrime<17>::value;
    std::cout << "Is 17 prime? " << (result ? "Yes" : "No") << std::endl; // Output: Yes
    return 0;
}