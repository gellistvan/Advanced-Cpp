#include <iostream>
#include <algorithm>

template <typename T>
class SimpleContainer {
public:
    SimpleContainer(std::initializer_list<T> init) : data(new T[init.size()]), size(init.size()) {
        std::copy(init.begin(), init.end(), data);
    }

    ~SimpleContainer() {
        delete[] data;
    }

    // Forward declaration of the iterator class
    class Iterator;

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }

private:
    T* data;
    std::size_t size;
};

template <typename T>
class SimpleContainer<T>::Iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(pointer ptr) : current(ptr) {}

    reference operator*() const { return *current; }
    pointer operator->() { return current; }

    Iterator& operator++() {
        ++current;
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp = *this;
        ++current;
        return tmp;
    }

    Iterator& operator--() {
        --current;
        return *this;
    }

    Iterator operator--(int) {
        Iterator tmp = *this;
        --current;
        return tmp;
    }

    Iterator operator+(difference_type n) const {
        return Iterator(current + n);
    }

    Iterator operator-(difference_type n) const {
        return Iterator(current - n);
    }

    difference_type operator-(const Iterator& other) const {
        return current - other.current;
    }

    Iterator& operator+=(difference_type n) {
        current += n;
        return *this;
    }

    Iterator& operator-=(difference_type n) {
        current -= n;
        return *this;
    }

    reference operator[](difference_type n) const {
        return current[n];
    }

    bool operator==(const Iterator& other) const {
        return current == other.current;
    }

    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }

    bool operator<(const Iterator& other) const {
        return current < other.current;
    }

    bool operator>(const Iterator& other) const {
        return current > other.current;
    }

    bool operator<=(const Iterator& other) const {
        return current <= other.current;
    }

    bool operator>=(const Iterator& other) const {
        return current >= other.current;
    }

private:
    pointer current;
};

int main() {
    SimpleContainer<int> container = {1, 2, 3, 4, 5};

    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Using reverse iteration
    for (auto it = container.end() - 1; it != container.begin() - 1; --it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    return 0;
}
