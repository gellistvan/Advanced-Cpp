#include <iostream>
#include <vector>
#include <forward_list>
#include <list>

void reading_from_input_iterator() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto it = vec.begin();

    while (it != vec.end()) {
        std::cout << *it << ' ';
        ++it;
    }
    std::cout << std::endl;
}

void output_iterator() {
    std::vector<int> vec(5);
    auto it = vec.begin();

    for (int i = 1; i <= 5; ++i) {
        *it = i;
        ++it;
    }

    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;
}

void forward_iterator() {
    std::forward_list<int> flist = {1, 2, 3, 4, 5};
    auto it = flist.begin();

    while (it != flist.end()) {
        std::cout << *it << ' ';
        ++it;
    }
    std::cout << std::endl;
}


void bidirectional_iterator() {
    std::list<int> lst = {1, 2, 3, 4, 5};
    auto it = lst.rbegin();  // Reverse iterator

    while (it != lst.rend()) {
        std::cout << *it << ' ';
        ++it;
    }
    std::cout << std::endl;
}

void random_access_iterator() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Forward iteration
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Reverse iteration
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Random access
    std::cout << "Element at index 2: " << vec[2] << std::endl;
}

int main() {
    reading_from_input_iterator();
    output_iterator();
    forward_iterator();
    bidirectional_iterator();
    random_access_iterator();
    return 0;
}