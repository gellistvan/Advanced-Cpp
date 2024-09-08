#include <vector>
#include <iostream>
// corrected from the book

template <typename T>
class DefaultAllocPolicy {
public:
    using value_type = T;

    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        ::operator delete(p);
    }
};

template <typename T>
class NoSortPolicy {
public:
    void sort(std::vector<T>&) {
        // No sorting performed
    }
};

template <typename T>
class AscendingSortPolicy {
public:
    void sort(std::vector<T>& container) {
        std::sort(container.begin(), container.end());
    }
};

template <typename T, template <typename> class AllocPolicy = DefaultAllocPolicy, template <typename> class SortPolicy = NoSortPolicy>
class CustomVector : private AllocPolicy<T>, private SortPolicy<T> {
public:
    using value_type = T;

    CustomVector() : data(nullptr), size(0), capacity(0) {}

    ~CustomVector() {
        clear();
        AllocPolicy<T>::deallocate(data, capacity);
    }

    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    void sort() {
        std::vector<T> temp(data, data + size);
        SortPolicy<T>::sort(temp);
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = temp[i];
        }
    }

    void print() const {
        for (std::size_t i = 0; i < size; ++i) {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }

private:
    T* data;
    std::size_t size;
    std::size_t capacity;

    void resize() {
        std::size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        T* new_data = AllocPolicy<T>::allocate(new_capacity);

        for (std::size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        AllocPolicy<T>::deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
    }

    void clear() {
        for (std::size_t i = 0; i < size; ++i) {
            data[i].~T();
        }
        size = 0;
    }
};

int main() {
    CustomVector<int, DefaultAllocPolicy, AscendingSortPolicy> vec;

    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(1);
    vec.push_back(5);

    vec.print();
    vec.sort();
    vec.print();

    return 0;
}