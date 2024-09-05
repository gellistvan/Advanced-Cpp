#include <iostream>
#include <type_traits>

// Helper trait to detect the presence of a 'print' member function
template<typename T>
class HasPrint {
private:
    template<typename U>
    static auto test(int) -> decltype(std::declval<U>().print(), std::true_type{});

    template<typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

// Class template
template<typename T>
class Printer {
public:
    // Enabled if T has a 'print' member function
    template<typename U = T>
    std::enable_if_t<HasPrint<U>::value, void> print() {
        static_cast<U*>(this)->print();
    }

    // Enabled if T does not have a 'print' member function
    template<typename U = T>
    std::enable_if_t<!HasPrint<U>::value, void> print() {
        std::cout << "No print member function." << std::endl;
    }
};

class WithPrint {
public:
    void print() {
        std::cout << "WithPrint::print()" << std::endl;
    }
};

class WithoutPrint {};

int main() {
    Printer<WithPrint> p1;
    p1.print(); // Output: WithPrint::print()

    Printer<WithoutPrint> p2;
    p2.print(); // Output: No print member function.
    return 0;
}
