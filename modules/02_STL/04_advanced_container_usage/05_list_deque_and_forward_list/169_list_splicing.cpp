#include <iostream>
#include <list>

int main() {
    std::list<int> list1 = {1, 2, 3};
    std::list<int> list2 = {4, 5, 6};

    // Splicing elements from list2 to list1
    auto it = list1.begin();
    std::advance(it, 1);
    list1.splice(it, list2);

    // Printing list1
    std::cout << "list1 after splicing: ";
    for (const auto& elem : list1) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    // Printing list2
    std::cout << "list2 after splicing: ";
    for (const auto& elem : list2) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    return 0;
}