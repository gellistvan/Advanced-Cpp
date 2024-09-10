#include <iostream>
#include <type_traits>

// Primary template handles non-integral types
template<typename T, typename = void>
struct IsIntegral : std::false_type {};

// Specialization for integral types
template<typename T>
struct IsIntegral<T, std::enable_if_t<std::is_integral_v<T>>> : std::true_type {};

int main() {
    std::cout << "Is int integral? " << IsIntegral<int>::value << std::endl; // Output: 1 (true)
    std::cout << "Is float integral? " << IsIntegral<float>::value << std::endl; // Output: 0 (false)
    return 0;
}