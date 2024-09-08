#include <iostream>
#include <cstring>
#include <queue>

class BufferPool {
    std::queue<char*> pool;
    size_t bufferSize;

public:
    BufferPool(size_t bufferSize, size_t initialCount) : bufferSize(bufferSize) {
        for (size_t i = 0; i < initialCount; ++i) {
            pool.push(new char[bufferSize]);
        }
    }

    ~BufferPool() {
        while (!pool.empty()) {
            delete[] pool.front();
            pool.pop();
        }
    }

    char* acquireBuffer() {
        if (pool.empty()) {
            return new char[bufferSize];
        } else {
            char* buffer = pool.front();
            pool.pop();
            return buffer;
        }
    }

    void releaseBuffer(char* buffer) {
        pool.push(buffer);
    }
};

int main() {
    BufferPool bufferPool(1024, 10);

    // Acquire and use a buffer
    char* buffer = bufferPool.acquireBuffer();
    std::strcpy(buffer, "Hello, buffer pool!");

    std::cout << "Buffer content: " << buffer << std::endl;

    // Release the buffer back to the pool
    bufferPool.releaseBuffer(buffer);

    return 0;
}