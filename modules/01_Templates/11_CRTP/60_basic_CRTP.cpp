#include <iostream>

template <typename Derived>
class Base {
public:
    void interface() {
        // Call the derived class implementation
        static_cast<Derived*>(this)->implementation();
    }

    // A default implementation
    void implementation() {
        std::cout << "Base implementation" << std::endl;
    }
};

class Derived : public Base<Derived> {
public:
    // Override the implementation
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};

int main() {
    Derived d;
    d.interface(); // Output: Derived implementation
    return 0;
}