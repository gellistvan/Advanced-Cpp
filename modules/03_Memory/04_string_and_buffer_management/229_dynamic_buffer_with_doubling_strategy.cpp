#include <iostream>
#include <cstring>

class DynamicBuffer {
    char* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        char* newData = new char[newCapacity];
        std::memcpy(newData, data, size);
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicBuffer() : data(new char[8]), size(0), capacity(8) {}

    ~DynamicBuffer() {
        delete[] data;
    }

    void append(const char* str, size_t len) {
        if (size + len > capacity) {
            resize(capacity * 2);
        }
        std::memcpy(data + size, str, len);
        size += len;
    }

    const char* getData() const {
        return data;
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    DynamicBuffer buffer;
    buffer.append("Hello, ", 7);
    buffer.append("world!", 6);

    std::cout << "Buffer content: " << std::string(buffer.getData(), buffer.getSize()) << std::endl;
    return 0;
}