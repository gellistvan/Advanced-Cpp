#include <iostream>
#include <memory>
#include <vector>

template <typename T, std::size_t PoolSize = 1024>
class PoolAllocator {
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
        using other = PoolAllocator<U, PoolSize>;
    };

    PoolAllocator() {
        pool = static_cast<pointer>(std::malloc(PoolSize * sizeof(T)));
        if (!pool) {
            throw std::bad_alloc();
        }
        free_blocks = PoolSize;
    }

    ~PoolAllocator() {
        std::free(pool);
    }

    pointer allocate(size_type n) {
        if (n > free_blocks) {
            throw std::bad_alloc();
        }
        pointer result = pool + allocated_blocks;
        allocated_blocks += n;
        free_blocks -= n;
        return result;
    }

    void deallocate(pointer p, size_type n) {
        // No-op for simplicity, but could implement free list
        free_blocks += n;
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
    pointer pool = nullptr;
    size_type allocated_blocks = 0;
    size_type free_blocks = 0;
};

int main() {
    std::vector<int, PoolAllocator<int>> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}