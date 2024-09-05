#include <functional>
#include <iostream>
#include <vector>
// corrected from the book

template <typename T>
void forEach(const std::vector<T>& vec, const std::function<void(const T&)>& func) {
    for (const auto& element : vec) {
        func(element);  // Invoke the callable function, abstracted by std::function
    }
}

void printNumber(const int& n) {
    std::cout << n << " ";
}

struct Multiplier {
    int factor;
    Multiplier(int f) : factor(f) {}
    void operator()(const int& n) const {
        std::cout << n * factor << " ";
    }
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Example 1: Lambda expression
    forEach(numbers, std::function<void(const int&)>([](const int& n) {
        std::cout << n << " ";
    }));
    std::cout << std::endl; // Output: 1 2 3 4 5

    // Example 2: Function pointer
    forEach(numbers, std::function<void(const int&)>(printNumber));
    std::cout << std::endl; // Output: 1 2 3 4 5

    // Example 3: Functor (Multiplies each number by 3)
    forEach(numbers, std::function<void(const int&)>(Multiplier(3)));
    std::cout << std::endl; // Output: 3 6 9 12 15

    return 0;
}
