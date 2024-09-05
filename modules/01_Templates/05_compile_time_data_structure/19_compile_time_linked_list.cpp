#include <iostream>

// Compile-time representation of an empty list
struct Nil {};

// Node template for the linked list
template<int Head, typename Tail = Nil>
struct List {
    static constexpr int head = Head;
    using tail = Tail;
};

// Function to print the compile-time list
void printList(Nil) {
    std::cout << "Nil" << std::endl;
}

template<int Head, typename Tail>
void printList(List<Head, Tail>) {
    std::cout << Head << " -> ";
    printList(Tail{});
}

int main() {
    using MyList = List<1, List<2, List<3, List<4>>>>;
    printList(MyList{});
    // Output: 1 -> 2 -> 3 -> 4 -> Nil
    return 0;
}