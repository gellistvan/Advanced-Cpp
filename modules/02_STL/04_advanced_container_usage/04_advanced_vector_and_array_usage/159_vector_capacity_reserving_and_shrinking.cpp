#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;
    vec.reserve(100); // Reserve space for 100 elements

    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }

    std::cout << "Vector size: " << vec.size() << std::endl;
    std::cout << "Vector capacity: " << vec.capacity() << std::endl;

    vec.erase(vec.begin() + 50, vec.end()); // Remove half the elements

    std::cout << "Vector size before shrink: " << vec.size() << std::endl;
    std::cout << "Vector capacity before shrink: " << vec.capacity() << std::endl;

    vec.shrink_to_fit();

    std::cout << "Vector size after shrink: " << vec.size() << std::endl;
    std::cout << "Vector capacity after shrink: " << vec.capacity() << std::endl;

    return 0;
}