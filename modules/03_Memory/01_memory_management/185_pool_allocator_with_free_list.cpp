#include <iostream>
#include <memory>
#include <vector>

template <typename T, std::size_t PoolSize = 1024>
class ImprovedPoolAllocator {
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
        using other = ImprovedPoolAllocator<U, PoolSize>;
    };

    ImprovedPoolAllocator() {
        pool = static_cast<pointer>(std::malloc(PoolSize * sizeof(T)));
        if (!pool) {
            throw std::bad_alloc();
        }
        free_list = nullptr;
        allocated_blocks = 0;
        free_blocks = PoolSize;
    }

    ~ImprovedPoolAllocator() {
        std::free(pool);
    }

    pointer allocate(size_type n) {
        if (n > 1 || free_blocks == 0) {
            throw std::bad_alloc();
        }
        if (free_list) {
            pointer result = free_list;
            free_list = *reinterpret_cast<pointer*>(free_list);
            --free_blocks;
            return result;
        } else {
            pointer result = pool + allocated_blocks++;
            --free_blocks;
            return result;
        }
    }

    void deallocate(pointer p, size_type n) {
        if (n > 1) return;
        *reinterpret_cast<pointer*>(p) = free_list;
        free_list = p;
        ++free_blocks;
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
    pointer free_list = nullptr;
    size_type allocated_blocks = 0;
    size_type free_blocks = 0;
};

int main() {
    std::vector<int, ImprovedPoolAllocator<int>> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}