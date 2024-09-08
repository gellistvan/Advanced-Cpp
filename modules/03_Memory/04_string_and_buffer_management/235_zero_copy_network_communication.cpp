#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sys/uio.h>

void exampleZeroCopyNetworkCommunication() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Accept a connection
    if ((client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Prepare data buffers for scatter-gather I/O
    std::vector<iovec> iov(2);
    char buffer1[] = "Hello, ";
    char buffer2[] = "world!";
    iov[0].iov_base = buffer1;
    iov[0].iov_len = sizeof(buffer1) - 1;
    iov[1].iov_base = buffer2;
    iov[1].iov_len = sizeof(buffer2) - 1;

    // Send data using scatter-gather I/O
    ssize_t sent = writev(client_fd, iov.data(), iov.size());
    if (sent == -1) {
        perror("writev failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Sent " << sent << " bytes using scatter-gather I/O." << std::endl;

    // Clean up
    close(client_fd);
    close(server_fd);
}

int main() {
    exampleZeroCopyNetworkCommunication();
    return 0;
}