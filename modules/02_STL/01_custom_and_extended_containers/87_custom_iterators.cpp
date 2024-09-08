#include <iterator>
#include <vector>
#include <iostream>

template <typename T>
class ReverseIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    ReverseIterator(pointer ptr) : current(ptr) {}

    reference operator*() const { return *current; }
    pointer operator->() { return current; }

    // Prefix increment
    ReverseIterator& operator++() {
        --current;
        return *this;
    }

    // Postfix increment
    ReverseIterator operator++(int) {
        ReverseIterator tmp = *this;
        --current;
        return tmp;
    }

    friend bool operator==(const ReverseIterator& a, const ReverseIterator& b) {
        return a.current == b.current;
    }

    friend bool operator!=(const ReverseIterator& a, const ReverseIterator& b) {
        return a.current != b.current;
    }

private:
    pointer current;
};

template <typename T>
class ReversibleVector : public std::vector<T> {
public:
    using std::vector<T>::vector;

    ReverseIterator<T> rbegin() {
        return ReverseIterator<T>(this->data() + this->size() - 1);
    }

    ReverseIterator<T> rend() {
        return ReverseIterator<T>(this->data() - 1);
    }
};

int main() {
    ReversibleVector<int> rv = {1, 2, 3, 4, 5};

    for (auto it = rv.rbegin(); it != rv.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    return 0;
}