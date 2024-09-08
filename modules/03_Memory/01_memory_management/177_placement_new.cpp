#include <iostream>
#include <new> // Required for placement new
#include <cstdlib> // Required for malloc and free

void examplePlacementNew() {
    // Allocate raw memory
    void* memory = std::malloc(sizeof(int));
    if (!memory) {
        throw std::bad_alloc();
    }

    // Construct an integer in the allocated memory
    int* intPtr = new (memory) int(42);
    std::cout << "Value: " << *intPtr << std::endl;

    // Free the raw memory
    std::free(memory);
}

int main() {
    examplePlacementNew();
    return 0;
}