#include <iostream>
#include <vector>
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

void examplePlacementNewWithVector() {
    const size_t count = 3;
    void* memory = std::malloc(sizeof(Example) * count);
    if (!memory) {
        throw std::bad_alloc();
    }

    std::vector<Example*> examples;
    for (size_t i = 0; i < count; ++i) {
        examples.push_back(new (&static_cast<Example*>(memory)[i]) Example(i + 1));
    }

    for (auto example : examples) {
        example->~Example();
    }

    std::free(memory);
}

int main() {
    examplePlacementNewWithVector();
    return 0;
}