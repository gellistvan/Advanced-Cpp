#include <iostream>
#include <forward_list>

int main() {
    std::forward_list<int> list1 = {1, 3, 5};
    std::forward_list<int> list2 = {2, 4, 6};

    list1.merge(list2);

    // Printing merged list
    std::cout << "Merged list: ";
    for (const auto& elem : list1) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    return 0;
}