#include <iostream>
#include <memory>
#include <type_traits>

// Primary template: T is not a smart pointer
template<typename T>
struct is_smart_pointer : std::false_type {};

// Specializations for std::unique_ptr and std::shared_ptr
template<typename T>
struct is_smart_pointer<std::unique_ptr<T>> : std::true_type {};

template<typename T>
struct is_smart_pointer<std::shared_ptr<T>> : std::true_type {};

// Function to demonstrate custom type trait
template<typename T>
void check_smart_pointer() {
    std::cout << std::boolalpha;
    std::cout << "is_smart_pointer<T>::value: " << is_smart_pointer<T>::value << std::endl;
}

int main() {
    std::cout << "Checking int:" << std::endl;
    check_smart_pointer<int>();

    std::cout << "\nChecking std::unique_ptr<int>:" << std::endl;
    check_smart_pointer<std::unique_ptr<int>>();

    std::cout << "\nChecking std::shared_ptr<int>:" << std::endl;
    check_smart_pointer<std::shared_ptr<int>>();

    return 0;
}
