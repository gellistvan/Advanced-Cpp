#include <iostream>
#include <memory>

struct CustomDeleter {
    void operator()(int* p) const {
        std::cout << "Custom deleting int: " << *p << std::endl;
        delete p;
    }
};

int main () {
    std::unique_ptr<int, CustomDeleter> ptr(new int(42));

    std::cout << "Value: " << *ptr << std::endl;

    // Transfer ownership
    std::unique_ptr<int, CustomDeleter> ptr2 = std::move(ptr);
    if (!ptr) {
        std::cout << "ptr1 is now null." << std::endl;
    }
    std::cout << "ptr2 Value: " << *ptr2 << std::endl;

    return 0;
}