#include <cstddef>
#include <iostream>
#include <vector>

template <typename T>
class PoolAllocator {
public:
    using value_type = T;

    PoolAllocator() noexcept : pool(nullptr), pool_size(0), free_list(nullptr) {}
    template <typename U>
    PoolAllocator(const PoolAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        if (n != 1) throw std::bad_alloc();

        if (!free_list) {
            allocate_pool();
        }

        T* result = reinterpret_cast<T*>(free_list);
        free_list = free_list->next;

        return result;
    }

    void deallocate(T* p, std::size_t n) noexcept {
        if (n != 1) return;

        reinterpret_cast<Node*>(p)->next = free_list;
        free_list = reinterpret_cast<Node*>(p);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) noexcept {
        p->~U();
    }

private:
    struct Node {
        Node* next;
    };

    void allocate_pool() {
        pool_size = 1024;
        pool = ::operator new(pool_size * sizeof(T));
        free_list = reinterpret_cast<Node*>(pool);

        Node* current = free_list;
        for (std::size_t i = 1; i < pool_size; ++i) {
            current->next = reinterpret_cast<Node*>(reinterpret_cast<char*>(pool) + i * sizeof(T));
            current = current->next;
        }
        current->next = nullptr;
    }

    void* pool;
    std::size_t pool_size;
    Node* free_list;
};

template <typename T, typename U>
bool operator==(const PoolAllocator<T>&, const PoolAllocator<U>&) noexcept {
    return true;
}

template <typename T, typename U>
bool operator!=(const PoolAllocator<T>&, const PoolAllocator<U>&) noexcept {
    return false;
}

int main() {
    std::vector<int, PoolAllocator<int>> vec;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}
