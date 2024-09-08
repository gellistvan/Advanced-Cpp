#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void manipulateLargeFile(const char* filename) {
    int fd = open(filename, O_RDWR);
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

    char* mapped = static_cast<char*>(mmap(nullptr, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0));
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return;
    }

    // Example: Convert all lowercase letters to uppercase
    for (size_t i = 0; i < sb.st_size; ++i) {
        if (mapped[i] >= 'a' && mapped[i] <= 'z') {
            mapped[i] -= 32;
        }
    }

    if (msync(mapped, sb.st_size, MS_SYNC) == -1) {
        perror("msync");
    }

    if (munmap(mapped, sb.st_size) == -1) {
        perror("munmap");
    }
    close(fd);
}

int main() {
    const char* filename = "/tmp/large_file.txt";
    manipulateLargeFile(filename);
    return 0;
}