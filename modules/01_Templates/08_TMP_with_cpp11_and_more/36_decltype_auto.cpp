#include <iostream>
#include <type_traits>

// Function to add two values
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

int main() {
    auto result = add(1, 2.5);
    std::cout << "Result of add(1, 2.5): " << result << std::endl; // Output: 3.5
    std::cout << "Type of result: " << typeid(result).name() << std::endl; // Output: d (double)
    return 0;
}