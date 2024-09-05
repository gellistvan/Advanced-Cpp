#include <iostream>
#include <type_traits>

// Function to demonstrate removing reference
template<typename T>
void remove_reference_demo() {
    using NonReferenceType = typename std::remove_reference<T>::type;
    std::cout << "Original type: " << typeid(T).name() << std::endl;
    std::cout << "Non-reference type: " << typeid(NonReferenceType).name() << std::endl;
}

int main() {
    std::cout << "Removing reference from int&:" << std::endl;
    remove_reference_demo<int&>();

    return 0;
}