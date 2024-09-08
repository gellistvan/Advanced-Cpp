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

    class Iterator;
    class ReverseIterator;

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
    ReverseIterator rbegin() { return ReverseIterator(data + size - 1); }
    ReverseIterator rend() { return ReverseIterator(data - 1); }

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

    bool operator==(const Iterator& other) const { return current == other.current; }
    bool operator!=(const Iterator& other) const { return current != other.current; }

private:
    pointer current;
};

template <typename T>
class SimpleContainer<T>::ReverseIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    ReverseIterator(pointer ptr) : current(ptr) {}

    reference operator*() const { return *current; }
    pointer operator->() { return current; }

    ReverseIterator& operator++() {
        --current;
        return *this;
    }

    ReverseIterator operator++(int) {
        ReverseIterator tmp = *this;
        --current;
        return tmp;
    }

    ReverseIterator& operator--() {
        ++current;
        return *this;
    }

    ReverseIterator operator--(int) {
        ReverseIterator tmp = *this;
        ++current;
        return tmp;
    }

    bool operator==(const ReverseIterator& other) const { return current == other.current; }
    bool operator!=(const ReverseIterator& other) const { return current != other.current; }

private:
    pointer current;
};

int main() {
    SimpleContainer<int> container = {1, 2, 3, 4, 5};

    std::cout << "Forward iteration: ";
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Reverse iteration: ";
    for (auto rit = container.rbegin(); rit != container.rend(); ++rit) {
        std::cout << *rit << ' ';
    }
    std::cout << std::endl;

    return 0;
}