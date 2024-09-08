#include <cstring>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

void exampleAnonymousMapping() {
    size_t length = 4096; // Size of the mapping
    int protection = PROT_READ | PROT_WRITE;
    int flags = MAP_ANONYMOUS | MAP_PRIVATE;

    // Create an anonymous mapping
    char* mapped = static_cast<char*>(mmap(nullptr, length, protection, flags, -1, 0));
    if (mapped == MAP_FAILED) {
        perror("mmap");
        return;
    }

    // Use the memory
    strcpy(mapped, "Hello, anonymous mapping!");
    std::cout << "Mapped content: " << mapped << std::endl;

    // Unmap the memory
    if (munmap(mapped, length) == -1) {
        perror("munmap");
    }
}

int main() {
    exampleAnonymousMapping();
    return 0;
}