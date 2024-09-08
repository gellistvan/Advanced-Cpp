#include <iostream>
#include <vector>
#include <mutex>

template <typename T>
class ObjectPool {
public:
    ObjectPool(size_t poolSize)
        : poolSize(poolSize), freeList(poolSize) {
        pool = static_cast<T*>(std::malloc(sizeof(T) * poolSize));
        if (!pool) {
            throw std::bad_alloc();
        }
        for (size_t i = 0; i < poolSize; ++i) {
            freeList[i] = pool + i;
        }
    }

    ~ObjectPool() {
        std::free(pool);
    }

    template <typename... Args>
    T* allocate(Args&&... args) {
        if (freeList.empty()) {
            throw std::bad_alloc();
        }
        T* obj = freeList.back();
        freeList.pop_back();
        new (obj) T(std::forward<Args>(args)...);
        return obj;
    }

    void deallocate(T* obj) {
        obj->~T();
        freeList.push_back(obj);
    }

private:
    size_t poolSize;
    T* pool;
    std::vector<T*> freeList;
};

class Example {
public:
    Example(int value) : value(value) {
        std::cout << "Example constructed with value: " << value << std::endl;
    }
    ~Example() {
        std::cout << "Example destroyed" << std::endl;
    }

private:
    int value;
};

void exampleObjectPool() {
    ObjectPool<Example> pool(10);
    Example* ex1 = pool.allocate(42);
    Example* ex2 = pool.allocate(43);
    pool.deallocate(ex1);
    Example* ex3 = pool.allocate(44);

    std::cout << "Object pool example executed successfully." << std::endl;

    pool.deallocate(ex2);
    pool.deallocate(ex3);
}

int main() {
    exampleObjectPool();
    return 0;
}