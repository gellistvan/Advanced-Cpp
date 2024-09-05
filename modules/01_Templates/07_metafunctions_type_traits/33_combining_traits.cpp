#include <iostream>
#include <type_traits>

// Type trait to add a pointer if not already a pointer
template<typename T>
struct add_pointer_if_not {
    using type = typename std::conditional<std::is_pointer<T>::value, T, typename std::add_pointer<T>::type>::type;
};

// Function to demonstrate the combined type trait
template<typename T>
void add_pointer_if_not_demo() {
    using ResultType = typename add_pointer_if_not<T>::type;
    std::cout << "Original type: " << typeid(T).name() << std::endl;
    std::cout << "Result type: " << typeid(ResultType).name() << std::endl;
}

int main() {
    std::cout << "Adding pointer to int:" << std::endl;
    add_pointer_if_not_demo<int>();

    std::cout << "\nAdding pointer to int*:" << std::endl;
    add_pointer_if_not_demo<int*>();

    return 0;
}