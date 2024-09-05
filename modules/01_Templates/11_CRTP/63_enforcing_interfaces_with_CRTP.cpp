#include <iostream>

template <typename Derived>
class Interface {
public:
    void call() {
        static_cast<Derived*>(this)->requiredMethod();
    }
};

class Implementation : public Interface<Implementation> {
public:
    void requiredMethod() {
        std::cout << "Implementation of required method" << std::endl;
    }
};

int main() {
    Implementation impl;
    impl.call(); // Output: Implementation of required method

    return 0;
}