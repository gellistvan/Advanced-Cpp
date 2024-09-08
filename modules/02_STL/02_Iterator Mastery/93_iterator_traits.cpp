#include <iostream>
#include <iterator>
#include <vector>

template <typename Iterator>
void print_iterator_info(Iterator it) {
    using traits = std::iterator_traits<Iterator>;
    std::cout << "Value type: " << typeid(typename traits::value_type).name() << std::endl;
    std::cout << "Difference type: " << typeid(typename traits::difference_type).name() << std::endl;
    std::cout << "Pointer type: " << typeid(typename traits::pointer).name() << std::endl;
    std::cout << "Reference type: " << typeid(typename traits::reference).name() << std::endl;
    std::cout << "Iterator category: " << typeid(typename traits::iterator_category).name() << std::endl;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto it = vec.begin();

    print_iterator_info(it);

    return 0;
}