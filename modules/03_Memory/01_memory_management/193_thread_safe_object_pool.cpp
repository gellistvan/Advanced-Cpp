#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <stdexcept>

class PooledObject {
public:
    PooledObject(int id) : id(id) {
        std::cout << "PooledObject constructed with ID: " << id << std::endl;
    }

    ~PooledObject() {
        std::cout << "PooledObject destroyed with ID: " << id << std::endl;
    }

    void reset(int newId) {
        id = newId;
        std::cout << "PooledObject reset with new ID: " << id << std::endl;
    }

    int getId() const {
        return id;
    }

private:
    int id;
};

class ThreadSafeObjectPool {
public:
    ThreadSafeObjectPool(size_t initialPoolSize) {
        for (size_t i = 0; i < initialPoolSize; ++i) {
            pool.push_back(std::make_unique<PooledObject>(i));
        }
    }

    PooledObject* acquireObject() {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (pool.empty()) {
            throw std::runtime_error("No available objects in the pool");
        }
        PooledObject* obj = pool.back().release();
        pool.pop_back();
        return obj;
    }

    void releaseObject(PooledObject* obj) {
        std::lock_guard<std::mutex> lock(poolMutex);
        pool.push_back(std::unique_ptr<PooledObject>(obj));
    }

private:
    std::vector<std::unique_ptr<PooledObject>> pool;
    std::mutex poolMutex;
};

int main() {
    const size_t initialPoolSize = 5;
    ThreadSafeObjectPool pool(initialPoolSize);

    // Acquire and release objects from the pool
    PooledObject* obj1 = pool.acquireObject();
    PooledObject* obj2 = pool.acquireObject();
    pool.releaseObject(obj1);
    PooledObject* obj3 = pool.acquireObject();
    obj3->reset(10);

    std::cout << "Thread-safe object pool pattern example executed successfully." << std::endl;

    // Clean up
    pool.releaseObject(obj2);
    pool.releaseObject(obj3);

    return 0;
}