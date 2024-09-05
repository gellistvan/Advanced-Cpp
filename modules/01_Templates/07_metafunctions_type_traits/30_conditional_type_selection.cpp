#include <iostream>
#include <type_traits>

// Custom metafunction class to select a type based on a condition
struct Conditional {
    template<bool Condition, typename TrueType, typename FalseType>
    struct apply {
        using type = TrueType;
    };

    template<typename TrueType, typename FalseType>
    struct apply<false, TrueType, FalseType> {
        using type = FalseType;
    };
};

int main() {
    using T1 = Conditional::apply<true, int, double>::type;
    using T2 = Conditional::apply<false, int, double>::type;

    std::cout << std::is_same<int, T1>::value << std::endl;   // Output: 1 (true)
    std::cout << std::is_same<double, T2>::value << std::endl; // Output: 1 (true)
    return 0;
}