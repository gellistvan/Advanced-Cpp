#include <iostream>
#include <stdexcept>
#include <iterator>

template <typename T>
class DynamicArrayIterator;

template <typename T>
class DynamicArray {
public:
    DynamicArray();
    explicit DynamicArray(std::size_t initial_capacity);
    ~DynamicArray();

    void push_back(const T& value);
    void pop_back();
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    std::size_t size() const;
    bool empty() const;

    using iterator = DynamicArrayIterator<T>;
    using const_iterator = DynamicArrayIterator<const T>;

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + length); }
    const_iterator begin() const { return const_iterator(data); }
    const_iterator end() const { return const_iterator(data + length); }

private:
    T* data;
    std::size_t capacity;
    std::size_t length;

    void resize(std::size_t new_capacity);
};


// Memory Management

template <typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), capacity(0), length(0) {}

template <typename T>
DynamicArray<T>::DynamicArray(std::size_t initial_capacity)
    : data(new T[initial_capacity]), capacity(initial_capacity), length(0) {}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
void DynamicArray<T>::resize(std::size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (std::size_t i = 0; i < length; ++i) {
        new_data[i] = std::move(data[i]);
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

// Adding and Removing Elements
template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (length == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[length++] = value;
}

template <typename T>
void DynamicArray<T>::pop_back() {
    if (length == 0) {
        throw std::out_of_range("Array is empty");
    }
    --length;
}

template <typename T>
T& DynamicArray<T>::operator[](std::size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](std::size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
std::size_t DynamicArray<T>::size() const {
    return length;
}

template <typename T>
bool DynamicArray<T>::empty() const {
    return length == 0;
}

// iterators
template <typename T>
class DynamicArrayIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    DynamicArrayIterator(pointer ptr) : current(ptr) {}

    reference operator*() const { return *current; }
    pointer operator->() { return current; }

    // Prefix increment
    DynamicArrayIterator& operator++() {
        ++current;
        return *this;
    }

    // Postfix increment
    DynamicArrayIterator operator++(int) {
        DynamicArrayIterator tmp = *this;
        ++current;
        return tmp;
    }

    friend bool operator==(const DynamicArrayIterator& a, const DynamicArrayIterator& b) {
        return a.current == b.current;
    }

    friend bool operator!=(const DynamicArrayIterator& a, const DynamicArrayIterator& b) {
        return a.current != b.current;
    }

private:
    pointer current;
};

template <typename T>
DynamicArrayIterator<T> begin(DynamicArray<T>& array) {
    return DynamicArrayIterator<T>(array.data);
}

template <typename T>
DynamicArrayIterator<T> end(DynamicArray<T>& array) {
    return DynamicArrayIterator<T>(array.data + array.size());
}

int main() {
    DynamicArray<int> da;

    for (int i = 0; i < 10; ++i) {
        da.push_back(i);
    }

    for (auto it = da.begin(); it != da.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    return 0;
}