#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>
#include <sys/wait.h>

void writerProcess(const char* filename) {
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return;
    }

    const char* message = "Hello from writer process!";
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

    memcpy(mapped, message, message_size);

    if (munmap(mapped, message_size) == -1) {
        perror("munmap");
    }
    close(fd);
}

void readerProcess(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        return;
    }

    char* mapped = static_cast<char*>(mmap(nullptr, sb.st_size, PROT_READ, MAP_SHARED, fd, 0));
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return;
    }

    std::cout << "Reader process read: " << mapped << std::endl;

    if (munmap(mapped, sb.st_size) == -1) {
        perror("munmap");
    }
    close(fd);
}

int main() {
    const char* filename = "/tmp/shared_memory.txt";

    pid_t pid = fork();
    if (pid == 0) {
        // Child process - reader
        sleep(1); // Ensure the writer runs first
        readerProcess(filename);
    } else if (pid > 0) {
        // Parent process - writer
        writerProcess(filename);
        wait(nullptr); // Wait for child process to finish
    } else {
        perror("fork");
    }

    return 0;
}