#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

void exampleMemoryProtection() {
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
    strcpy(mapped, "Hello, memory protection!");
    std::cout << "Mapped content: " << mapped << std::endl;

    // Change memory protection to read-only
    if (mprotect(mapped, length, PROT_READ) == -1) {
        perror("mprotect");
        munmap(mapped, length);
        return;
    }

    // Try to write to the read-only memory (this should fail)
    strcpy(mapped, "This will fail");

    // Unmap the memory
    if (munmap(mapped, length) == -1) {
        perror("munmap");
    }
}

int main() {
    exampleMemoryProtection();
    return 0;
}