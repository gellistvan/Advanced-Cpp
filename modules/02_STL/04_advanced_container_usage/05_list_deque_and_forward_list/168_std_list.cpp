#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    // Iterating over the list
    for (const auto& elem : lst) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    // Inserting elements
    auto it = lst.begin();
    std::advance(it, 2);
    lst.insert(it, 10);

    // Deleting elements
    lst.erase(it);

    // Printing updated list
    for (const auto& elem : lst) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    return 0;
}