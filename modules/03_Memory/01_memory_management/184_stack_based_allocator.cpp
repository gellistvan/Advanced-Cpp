#include <iostream>
#include <memory>
#include <vector>

template <typename T, std::size_t StackSize = 1024>
class StackAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template <typename U>
    struct rebind {
        using other = StackAllocator<U, StackSize>;
    };

    StackAllocator() : stack_pointer(stack) {}

    pointer allocate(size_type n) {
        if (stack_pointer + n > stack + StackSize) {
            throw std::bad_alloc();
        }
        pointer result = stack_pointer;
        stack_pointer += n;
        return result;
    }

    void deallocate(pointer p, size_type n) {
        if (p + n == stack_pointer) {
            stack_pointer = p;
        }
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) {
        p->~U();
    }

private:
    T stack[StackSize];
    pointer stack_pointer;
};

int main() {
    std::vector<int, StackAllocator<int>> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}