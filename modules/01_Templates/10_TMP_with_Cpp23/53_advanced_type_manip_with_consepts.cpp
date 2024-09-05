#include <iostream>
#include <type_traits>

// Define a concept for copyable types
template<typename T>
concept Copyable = std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>;

// Function template using the Copyable concept
template<Copyable T>
T copy_value(const T& value) {
    return value;
}

int main() {
    int x = 42;
    std::cout << "Copy of x: " << copy_value(x) << std::endl; // Output: Copy of x: 42

    // std::unique_ptr<int> ptr = std::make_unique<int>(42);
    // std::cout << "Copy of ptr: " << copy_value(ptr) << std::endl; // Error: no matching function to call 'copy_value'

    return 0;
}