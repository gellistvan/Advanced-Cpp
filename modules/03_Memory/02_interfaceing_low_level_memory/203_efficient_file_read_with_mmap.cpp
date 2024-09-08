#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void exampleEfficientFileReading(const char* filename) {
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

    char* mapped = static_cast<char*>(mmap(nullptr, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return;
    }

    // Efficiently read the file contents
    std::string content(mapped, sb.st_size);
    std::cout << "File content: " << content << std::endl;

    if (munmap(mapped, sb.st_size) == -1) {
        perror("munmap");
    }
    close(fd);
}

int main() {
    const char* filename = "large_file.txt";
    exampleEfficientFileReading(filename);
    return 0;
}