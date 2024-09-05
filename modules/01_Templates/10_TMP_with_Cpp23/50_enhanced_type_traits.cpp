#include <iostream>
#include <type_traits>

// Custom type trait to check if a type is a const pointer
template<typename T>
struct is_const_pointer : std::false_type {};

template<typename T>
struct is_const_pointer<const T*> : std::true_type {};

// Using new type traits in C++23
int main() {
    std::cout << std::boolalpha;
    std::cout << "is_const_pointer<int>::value: " << is_const_pointer<int>::value << std::endl; // Output: false
    std::cout << "is_const_pointer<const int*>::value: " << is_const_pointer<const int*>::value << std::endl; // Output: true
    return 0;
}