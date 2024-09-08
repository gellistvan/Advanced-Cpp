#include <iostream>
#include <vector>
#include <mutex>

template <typename T>
class ObjectPool {
public:
    ObjectPool(size_t poolSize)
        : poolSize(poolSize) {
        pool = static_cast<T*>(std::malloc(sizeof(T) * poolSize));
        if (!pool) {
            throw std::bad_alloc();
        }
        freeList.resize(poolSize, nullptr);
        for (size_t i = 0; i < poolSize; ++i) {
            freeList[i] = pool + i;
        }
        freeIndex = poolSize - 1;
    }

    ~ObjectPool() {
        for (size_t i = 0; i < poolSize; ++i) {
            if (freeList[i] != nullptr) {
                freeList[i]->~T();
            }
        }
        std::free(pool);
    }

    template <typename... Args>
    T* allocate(Args&&... args) {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (freeIndex == SIZE_MAX) {
            throw std::bad_alloc();
        }
        T* obj = freeList[freeIndex--];
        new (obj) T(std::forward<Args>(args)...);
        return obj;
    }

    void deallocate(T* obj) {
        std::lock_guard<std::mutex> lock(poolMutex);
        obj->~T();
        if (freeIndex == poolSize - 1) {
            throw std::bad_alloc();
        }
        freeList[++freeIndex] = obj;
    }

private:
    size_t poolSize;
    T* pool;
    std::vector<T*> freeList;
    size_t freeIndex;
    std::mutex poolMutex;
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

int main() {
    const size_t poolSize = 10;

    ObjectPool<Example> pool(poolSize);

    // Allocate and deallocate objects from the pool
    Example* ex1 = pool.allocate(42);
    Example* ex2 = pool.allocate(43);
    pool.deallocate(ex1);
    Example* ex3 = pool.allocate(44);

    std::cout << "Object pool example executed successfully." << std::endl;

    pool.deallocate(ex2);
    pool.deallocate(ex3);

    return 0;
}