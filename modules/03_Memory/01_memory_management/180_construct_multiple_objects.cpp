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

void exampleMultipleObjects() {
    const size_t count = 3;
    void* memory = std::malloc(sizeof(Example) * count);
    if (!memory) {
        throw std::bad_alloc();
    }

    Example* exampleArray = static_cast<Example*>(memory);
    for (size_t i = 0; i < count; ++i) {
        new (&exampleArray[i]) Example(i + 1);
    }

    for (size_t i = 0; i < count; ++i) {
        exampleArray[i].~Example();
    }

    std::free(memory);
}

int main() {
    exampleMultipleObjects();
    return 0;
}