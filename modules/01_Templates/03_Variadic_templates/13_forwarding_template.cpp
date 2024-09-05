#include <iostream>
#include <memory>

// Factory function using variadic templates and perfect forwarding
template<typename T, typename... Args>
std::unique_ptr<T> create(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

class MyClass {
public:
    MyClass(int x, double y) {
        std::cout << "MyClass constructor called with x = " << x << " and y = " << y << std::endl;
    }
};

int main() {
    auto obj = create<MyClass>(42, 3.14);
    // Output: MyClass constructor called with x = 42 and y = 3.14
    return 0;
}