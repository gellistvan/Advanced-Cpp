#include <iostream>
#include <vector>
#include <mutex>

class ThreadSafeMemoryPool {
public:
    ThreadSafeMemoryPool(size_t blockSize, size_t poolSize)
        : blockSize(blockSize), poolSize(poolSize) {
        pool = static_cast<char*>(std::malloc(blockSize * poolSize));
        if (!pool) {
            throw std::bad_alloc();
        }
        freeList.resize(poolSize, nullptr);
        for (size_t i = 0; i < poolSize; ++i) {
            freeList[i] = pool + i * blockSize;
        }
        freeIndex = poolSize - 1;
    }

    ~ThreadSafeMemoryPool() {
        std::free(pool);
    }

    void* allocate() {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (freeIndex == SIZE_MAX) {
            throw std::bad_alloc();
        }
        return freeList[freeIndex--];
    }

    void deallocate(void* ptr) {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (freeIndex == poolSize - 1) {
            throw std::bad_alloc();
        }
        freeList[++freeIndex] = static_cast<char*>(ptr);
    }

private:
    size_t blockSize;
    size_t poolSize;
    char* pool;
    std::vector<char*> freeList;
    size_t freeIndex;
    std::mutex poolMutex;
};

int main() {
    const size_t blockSize = 32;
    const size_t poolSize = 10;

    ThreadSafeMemoryPool pool(blockSize, poolSize);

    // Allocate and deallocate memory from the pool
    void* ptr1 = pool.allocate();
    void* ptr2 = pool.allocate();
    pool.deallocate(ptr1);
    void* ptr3 = pool.allocate();

    std::cout << "Thread-safe memory pool example executed successfully." << std::endl;

    return 0;
}