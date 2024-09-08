#include <iostream>
#include <vector>
#include <memory>

template <typename T>
struct CustomAllocator : public std::allocator<T> {
    using Base = std::allocator<T>;
    using pointer = typename std::allocator_traits<Base>::pointer;
    using size_type = typename std::allocator_traits<Base>::size_type;

    T* allocate(size_type n, const void* hint = 0) {
        std::cout << "Allocating " << n << " elements" << std::endl;
        return std::allocator_traits<Base>::allocate(*this, n, hint);
    }

    void deallocate(pointer p, size_type n) {
        std::cout << "Deallocating " << n << " elements" << std::endl;
        std::allocator_traits<Base>::deallocate(*this, p, n);
    }
};

int main() {
    std::vector<int, CustomAllocator<int>> vec;
    vec.reserve(10);

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    return 0;
}