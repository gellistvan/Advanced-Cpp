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

class ResizableObjectPool {
public:
    ResizableObjectPool(size_t initialPoolSize) : nextId(initialPoolSize) {
        for (size_t i = 0; i < initialPoolSize; ++i) {
            pool.push_back(std::make_unique<PooledObject>(i));
        }
    }

    PooledObject* acquireObject() {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (pool.empty()) {
            expandPool();
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
    void expandPool() {
        for (size_t i = 0; i < poolExpansionSize; ++i) {
            pool.push_back(std::make_unique<PooledObject>(nextId++));
        }
        std::cout << "Pool expanded to size: " << pool.size() << std::endl;
    }

    static constexpr size_t poolExpansionSize = 5;
    size_t nextId;
    std::vector<std::unique_ptr<PooledObject>> pool;
    std::mutex poolMutex;
};

int main() {
    const size_t initialPoolSize = 5;
    ResizableObjectPool pool(initialPoolSize);

    // Acquire and release objects from the pool
    PooledObject* obj1 = pool.acquireObject();
    PooledObject* obj2 = pool.acquireObject();
    pool.releaseObject(obj1);
    PooledObject* obj3 = pool.acquireObject();
    obj3->reset(10);

    // Simulate pool expansion
    for (int i = 0; i < 10; ++i) {
        pool.acquireObject();
    }

    std::cout << "Resizable object pool pattern example executed successfully." << std::endl;

    // Clean up
    pool.releaseObject(obj2);
    pool.releaseObject(obj3);

    return 0;
}