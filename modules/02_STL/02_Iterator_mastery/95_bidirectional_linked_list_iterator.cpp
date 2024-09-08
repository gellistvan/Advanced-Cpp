#include <iostream>

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(const T& value) {
        Node* new_node = new Node{value, tail, nullptr};
        if (tail) {
            tail->next = new_node;
        } else {
            head = new_node;
        }
        tail = new_node;
    }

    class Iterator;

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

private:
    Node* head;
    Node* tail;
};

template <typename T>
class LinkedList<T>::Iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(Node* ptr) : current(ptr) {}

    reference operator*() const { return current->data; }
    pointer operator->() { return &current->data; }

    Iterator& operator++() {
        current = current->next;
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp = *this;
        current = current->next;
        return tmp;
    }

    Iterator& operator--() {
        current = current->prev;
        return *this;
    }

    Iterator operator--(int) {
        Iterator tmp = *this;
        current = current->prev;
        return tmp;
    }

    bool operator==(const Iterator& other) const {
        return current == other.current;
    }

    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }

private:
    Node* current;
};

int main() {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    for (auto it = --list.end(); it != --list.begin(); --it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;




    return 0;
}