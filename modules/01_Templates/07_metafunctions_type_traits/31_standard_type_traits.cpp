#include <iostream>
#include <type_traits>

// Function to demonstrate type traits
template<typename T>
void check_type_traits() {
    std::cout << std::boolalpha;
    std::cout << "std::is_integral<T>::value: " << std::is_integral<T>::value << std::endl;
    std::cout << "std::is_floating_point<T>::value: " << std::is_floating_point<T>::value << std::endl;
    std::cout << "std::is_pointer<T>::value: " << std::is_pointer<T>::value << std::endl;
    std::cout << "std::is_reference<T>::value: " << std::is_reference<T>::value << std::endl;
}

int main() {
    std::cout << "Checking int:" << std::endl;
    check_type_traits<int>();

    std::cout << "\nChecking float:" << std::endl;
    check_type_traits<float>();

    std::cout << "\nChecking int*:" << std::endl;
    check_type_traits<int*>();

    std::cout << "\nChecking int&:" << std::endl;
    check_type_traits<int&>();

    return 0;
}