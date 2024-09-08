#include <iostream>
#include <deque>

int main() {
    std::deque<int> dq = {1, 2, 3, 4, 5};

    // Iterating over the deque
    for (const auto& elem : dq) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    // Insert elements at both ends
    dq.push_front(0);
    dq.push_back(6);

    // Remove elements from both ends
    dq.pop_front();
    dq.pop_back();

    // Printing updated deque
    for (const auto& elem : dq) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    return 0;
}