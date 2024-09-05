#include <iostream>

// Metafunction class to calculate GCD
struct GCD {
    template<int A, int B>
    struct apply {
        static constexpr int value = GCD::apply<B, A % B>::value;
    };

    template<int A>
    struct apply<A, 0> {
        static constexpr int value = A;
    };
};

int main() {
    constexpr int result = GCD::apply<48, 18>::value;
    std::cout << "GCD of 48 and 18 is " << result << std::endl; // Output: 6
    return 0;
}