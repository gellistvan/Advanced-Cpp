#include <iostream>
#include <vector>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>

void exampleScatterGatherIO(const char* filename) {
    // Open the file for writing
    int fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return;
    }

    // Prepare data buffers
    std::vector<iovec> iov(2);
    char buffer1[] = "Hello, ";
    char buffer2[] = "world!";
    iov[0].iov_base = buffer1;
    iov[0].iov_len = sizeof(buffer1) - 1;
    iov[1].iov_base = buffer2;
    iov[1].iov_len = sizeof(buffer2) - 1;

    // Write data using scatter-gather I/O
    ssize_t written = writev(fd, iov.data(), iov.size());
    if (written == -1) {
        perror("writev");
        close(fd);
        return;
    }

    std::cout << "Written " << written << " bytes using scatter-gather I/O." << std::endl;

    // Close the file descriptor
    close(fd);
}

int main() {
    const char* filename = "scatter_gather.txt";
    exampleScatterGatherIO(filename);
    return 0;
}