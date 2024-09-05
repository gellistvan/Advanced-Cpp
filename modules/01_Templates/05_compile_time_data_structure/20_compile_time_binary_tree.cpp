#include <iostream>

// Compile-time representation of an empty tree
struct EmptyTree {};

// Node template for the binary tree
template<int Value, typename Left = EmptyTree, typename Right = EmptyTree>
struct Tree {
    static constexpr int value = Value;
    using left = Left;
    using right = Right;
};

// Function to print the compile-time binary tree (in-order traversal)
void printTree(EmptyTree) {}

template<int Value, typename Left, typename Right>
void printTree(Tree<Value, Left, Right>) {
    printTree(Left{});
    std::cout << Value << " ";
    printTree(Right{});
}

int main() {
    using MyTree = Tree<4, Tree<2, Tree<1>, Tree<3>>, Tree<6, Tree<5>, Tree<7>>>;
    printTree(MyTree{});
    // Output: 1 2 3 4 5 6 7
    return 0;
}