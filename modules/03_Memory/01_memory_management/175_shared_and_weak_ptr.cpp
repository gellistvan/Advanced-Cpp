#include <iostream>
#include <memory>

void exampleSharedPtr() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::shared_ptr<int> ptr2 = ptr1;

    std::cout << "ptr1 Value: " << *ptr1 << std::endl;
    std::cout << "ptr2 Value: " << *ptr2 << std::endl;
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
}

void exampleWeakPtr() {
    std::shared_ptr<int> sptr = std::make_shared<int>(42);
    std::weak_ptr<int> wptr = sptr;

    std::cout << "Reference count: " << sptr.use_count() << std::endl;

    if (auto spt = wptr.lock()) { // Create a shared_ptr from weak_ptr
        std::cout << "Locked Value: " << *spt << std::endl;
    } else {
        std::cout << "wptr is expired." << std::endl;
    }
}


struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    ~Node() {
        std::cout << "Node destroyed" << std::endl;
    }
};

int main() {
    exampleSharedPtr();
    exampleWeakPtr();

    std::shared_ptr<Node> node1 = std::make_shared<Node>();
    std::shared_ptr<Node> node2 = std::make_shared<Node>();

    node1->next = node2;
    node2->prev = node1;

    // Breaking the cycle using weak_ptr
    node1.reset();
    node2.reset();

    return 0;
}