#include <iostream>
#include <vector>
#include <mutex>

class NetworkPacket {
public:
    NetworkPacket(int id, const std::string& data) : id(id), data(data) {
        std::cout << "NetworkPacket constructed with ID: " << id << " and data: " << data << std::endl;
    }
    ~NetworkPacket() {
        std::cout << "NetworkPacket destroyed with ID: " << id << std::endl;
    }

private:
    int id;
    std::string data;
};

template <typename T>
class NetworkPacketPool {
public:
    NetworkPacketPool(size_t poolSize)
        : poolSize(poolSize), freeList(poolSize) {
        pool = static_cast<T*>(std::malloc(sizeof(T) * poolSize));
        if (!pool) {
            throw std::bad_alloc();
        }
        for (size_t i = 0; i < poolSize; ++i) {
            freeList[i] = pool + i;
        }
    }

    ~NetworkPacketPool() {
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

void exampleNetworkPacketPool() {
    NetworkPacketPool<NetworkPacket> pool(10);
    NetworkPacket* np1 = pool.allocate(1, "Hello, World!");
    NetworkPacket* np2 = pool.allocate(2, "Goodbye, World!");
    pool.deallocate(np1);
    NetworkPacket* np3 = pool.allocate(3, "Hello again!");

    std::cout << "Network packet pool example executed successfully." << std::endl;

    pool.deallocate(np2);
    pool.deallocate(np3);
}

int main() {
    exampleNetworkPacketPool();
    return 0;
}