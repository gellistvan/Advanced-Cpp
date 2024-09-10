#include <iostream>
#include <type_traits>

// General template for printing values
template<typename T>
void printValue(T value, std::false_type) {
    std::cout << "Value: " << value << std::endl;
}

// Specialization for printing pointers
template<typename T>
void printValue(T value, std::true_type) {
    if (value) {
        std::cout << "Pointer value: " << *value << std::endl;
    } else {
        std::cout << "Null pointer" << std::endl;
    }
}

// Wrapper function that dispatches to the correct print function
template<typename T>
void printValue(T value) {
    printValue(value, std::is_pointer<T>{});
}

int main() {
    int x = 42;
    int* ptr = &x;
    int* nullPtr = nullptr;

    printValue(x);       // Output: Value: 42
    printValue(ptr);     // Output: Pointer value: 42
    printValue(nullPtr); // Output: Null pointer

    return 0;
}
