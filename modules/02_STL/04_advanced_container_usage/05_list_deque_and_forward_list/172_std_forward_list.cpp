#include <iostream>
#include <forward_list>

int main() {
    std::forward_list<int> flst = {1, 2, 3, 4, 5};

    // Iterating over the forward_list
    for (const auto& elem : flst) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    // Inserting elements
    flst.push_front(0);

    // Deleting elements
    flst.pop_front();

    // Printing updated forward_list
    for (const auto& elem : flst) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    return 0;
}