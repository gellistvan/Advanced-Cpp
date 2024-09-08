#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void exampleMemoryMappedFile(const char* filename) {
    // Open the file for reading
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    // Get the file size
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        return;
    }

    // Map the file into memory
    char* mapped = static_cast<char*>(mmap(nullptr, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return;
    }

    // Access the file contents
    for (size_t i = 0; i < sb.st_size; ++i) {
        std::cout << mapped[i];
    }
    std::cout << std::endl;

    // Unmap the file and close the file descriptor
    if (munmap(mapped, sb.st_size) == -1) {
        perror("munmap");
    }
    close(fd);
}

int main() {
    const char* filename = "/tmp/example.txt";
    exampleMemoryMappedFile(filename);
    return 0;
}