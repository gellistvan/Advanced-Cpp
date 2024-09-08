#include <iostream>
#include <new>
#include <vector>
#include <cstdlib>

class CustomAllocator {
public:
    CustomAllocator(size_t size) {
        memoryPool = std::malloc(size);
        if (!memoryPool) {
            throw std::bad_alloc();
        }
    }

    ~CustomAllocator() {
        std::free(memoryPool);
    }

    void* allocate(size_t size) {
        if (offset + size > poolSize) {
            throw std::bad_alloc();
        }
        void* ptr = static_cast<char*>(memoryPool) + offset;
        offset += size;
        return ptr;
    }

    void deallocate(void* ptr) {
        // No-op for simplicity
    }

private:
    void* memoryPool;
    size_t offset = 0;
    size_t poolSize = 1024; // Example pool size
};

void exampleCustomAllocator() {
    CustomAllocator allocator(1024);

    void* mem = allocator.allocate(sizeof(int));
    int* intPtr = new (mem) int(42);
    std::cout << "Allocated integer value: " << *intPtr << std::endl;

    allocator.deallocate(static_cast<void*>(mem));
}

int main() {
    exampleCustomAllocator();
    return 0;
}