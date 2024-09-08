#include <iostream>
#include <vector>
#include <mutex>

class SensorData {
public:
    SensorData(int id, float value) : id(id), value(value) {
        std::cout << "SensorData constructed with ID: " << id << " and value: " << value << std::endl;
    }
    ~SensorData() {
        std::cout << "SensorData destroyed with ID: " << id << std::endl;
    }

private:
    int id;
    float value;
};

template <typename T>
class SensorDataPool {
public:
    SensorDataPool(size_t poolSize)
        : poolSize(poolSize), freeList(poolSize) {
        pool = static_cast<T*>(std::malloc(sizeof(T) * poolSize));
        if (!pool) {
            throw std::bad_alloc();
        }
        for (size_t i = 0; i < poolSize; ++i) {
            freeList[i] = pool + i;
        }
    }

    ~SensorDataPool() {
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

void exampleSensorDataPool() {
    SensorDataPool<SensorData> pool(10);
    SensorData* sd1 = pool.allocate(1, 25.5f);
    SensorData* sd2 = pool.allocate(2, 30.2f);
    pool.deallocate(sd1);
    SensorData* sd3 = pool.allocate(3, 22.8f);

    std::cout << "Sensor data pool example executed successfully." << std::endl;

    pool.deallocate(sd2);
    pool.deallocate(sd3);
}

int main() {
    exampleSensorDataPool();
    return 0;
}