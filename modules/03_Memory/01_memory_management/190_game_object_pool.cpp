#include <iostream>
#include <vector>
#include <mutex>

class GameObject {
public:
    GameObject(int id) : id(id) {
        std::cout << "GameObject constructed with ID: " << id << std::endl;
    }
    ~GameObject() {
        std::cout << "GameObject destroyed with ID: " << id << std::endl;
    }

private:
    int id;
};

template <typename T>
class GameObjectPool {
public:
    GameObjectPool(size_t poolSize)
        : poolSize(poolSize), freeList(poolSize) {
        pool = static_cast<T*>(std::malloc(sizeof(T) * poolSize));
        if (!pool) {
            throw std::bad_alloc();
        }
        for (size_t i = 0; i < poolSize; ++i) {
            freeList[i] = pool + i;
        }
    }

    ~GameObjectPool() {
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

void exampleGameObjectPool() {
    GameObjectPool<GameObject> pool(10);
    GameObject* go1 = pool.allocate(1);
    GameObject* go2 = pool.allocate(2);
    pool.deallocate(go1);
    GameObject* go3 = pool.allocate(3);

    std::cout << "Game object pool example executed successfully." << std::endl;

    pool.deallocate(go2);
    pool.deallocate(go3);
}

int main() {
    exampleGameObjectPool();
    return 0;
}