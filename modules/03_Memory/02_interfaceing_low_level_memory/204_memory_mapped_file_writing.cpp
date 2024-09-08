#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

void exampleMemoryMappedFileWriting(const char* filename) {
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return;
    }

    const char* message = "Hello, memory-mapped file!";
    size_t message_size = strlen(message) + 1;

    if (ftruncate(fd, message_size) == -1) {
        perror("ftruncate");
        close(fd);
        return;
    }

    char* mapped = static_cast<char*>(mmap(nullptr, message_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return;
    }

    // Write to the memory-mapped file
    memcpy(mapped, message, message_size);

    // Ensure changes are written to the file
    if (msync(mapped, message_size, MS_SYNC) == -1) {
        perror("msync");
    }

    if (munmap(mapped, message_size) == -1) {
        perror("munmap");
    }
    close(fd);
}

int main() {
    const char* filename = "/tmp/mapped_file.txt";
    exampleMemoryMappedFileWriting(filename);
    return 0;
}