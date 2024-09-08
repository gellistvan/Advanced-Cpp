#include <iostream>
#include <new>
#include <cstdlib>

class Example {
public:
    Example(int x) : x(x) {
        std::cout << "Example constructed with value: " << x << std::endl;
    }
    ~Example() {
        std::cout << "Example destroyed" << std::endl;
    }

private:
    int x;
};

void exampleObjectLifetime() {
    void* memory = std::malloc(sizeof(Example));
    if (!memory) {
        throw std::bad_alloc();
    }

    Example* examplePtr = new (memory) Example(42);
    examplePtr->~Example();

    std::free(memory);
}

int main() {
    exampleObjectLifetime();
    return 0;
}