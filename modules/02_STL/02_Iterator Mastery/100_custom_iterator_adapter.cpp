#include <iterator>
#include <functional>
#include <iostream>
#include <vector>
#include <cmath>

template <typename

 Iterator, typename Func>
class TransformIterator {
public:
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type = typename std::result_of<Func(typename std::iterator_traits<Iterator>::reference)>::type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using pointer = value_type*;
    using reference = value_type;

    TransformIterator(Iterator it, Func func) : current(it), transform_func(func) {}

    reference operator*() const { return transform_func(*current); }
    pointer operator->() const { return &transform_func(*current); }

    TransformIterator& operator++() {
        ++current;
        return *this;
    }

    TransformIterator operator++(int) {
        TransformIterator tmp = *this;
        ++current;
        return tmp;
    }

    bool operator==(const TransformIterator& other) const { return current == other.current; }
    bool operator!=(const TransformIterator& other) const { return current != other.current; }

private:
    Iterator current;
    Func transform_func;
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    auto transform_func = [](int x) { return std::sqrt(x); };
    TransformIterator<std::vector<int>::iterator, decltype(transform_func)> begin(vec.begin(), transform_func);
    TransformIterator<std::vector<int>::iterator, decltype(transform_func)> end(vec.end(), transform_func);

    std::cout << "Transformed vector: ";
    for (auto it = begin; it != end; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    return 0;
}