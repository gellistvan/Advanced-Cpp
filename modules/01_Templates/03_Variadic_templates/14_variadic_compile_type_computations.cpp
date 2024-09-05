#include <iostream>
#include <type_traits>

// Helper struct to check if all types are the same
template<typename T, typename... Args>
struct are_all_same;

template<typename T>
struct are_all_same<T> : std::true_type {};

template<typename T, typename U, typename... Args>
struct are_all_same<T, U, Args...> : std::false_type {};

template<typename T, typename... Args>
struct are_all_same<T, T, Args...> : are_all_same<T, Args...> {};

// Function that uses the are_all_same trait
template<typename T, typename... Args>
std::enable_if_t<are_all_same<T, Args...>::value, void> check_types(T, Args...) {
    std::cout << "All arguments are of the same type." << std::endl;
}

template<typename T, typename... Args>
std::enable_if_t<!are_all_same<T, Args...>::value, void> check_types(T, Args...) {
    std::cout << "Arguments are of different types." << std::endl;
}

int main() {
    check_types(1, 2, 3);          // Output: All arguments are of the same type.
    check_types(1, 2.0, 3);        // Output: Arguments are of different types.
    check_types("Hello", "World"); // Output: All arguments are of the same type.
    return 0;
}