#include <iostream>
#include <unordered_map>
#include <functional>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <cstring>

// Handle type alias for readability
using Handle = int;

// Event Handler Interface
class EventHandler {
public:
    virtual ~EventHandler() = default;
    virtual void handleEvent(Handle handle) = 0;
};

// Reactor Class
class Reactor {
public:
    Reactor() {
        epoll_fd = epoll_create1(0);
        if (epoll_fd == -1) {
            throw std::runtime_error("Failed to create epoll instance");
        }
    }

    ~Reactor() {
        close(epoll_fd);
    }

    void registerHandler(Handle handle, EventHandler* handler) {
        struct epoll_event event;
        event.data.fd = handle;
        event.events = EPOLLIN;

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, handle, &event) == -1) {
            throw std::runtime_error("Failed to add handle to epoll instance");
        }

        handlers[handle] = handler;
    }

    void removeHandler(Handle handle) {
        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, handle, nullptr) == -1) {
            throw std::runtime_error("Failed to remove handle from epoll instance");
        }

        handlers.erase(handle);
    }

    void run() {
        const int MAX_EVENTS = 10;
        struct epoll_event events[MAX_EVENTS];

        while (true) {
            int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
            if (num_events == -1) {
                if (errno == EINTR) {
                    continue;
                } else {
                    throw std::runtime_error("epoll_wait failed");
                }
            }

            for (int i = 0; i < num_events; ++i) {
                Handle handle = events[i].data.fd;
                if (handlers.find(handle) != handlers.end()) {
                    handlers[handle]->handleEvent(handle);
                }
            }
        }
    }

private:
    Handle epoll_fd;
    std::unordered_map<Handle, EventHandler*> handlers;
};


class EchoServer : public EventHandler {
public:
    EchoServer(int port) {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            throw std::runtime_error("Failed to create socket");
        }

        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            throw std::runtime_error("Failed to bind socket");
        }

        if (listen(server_fd, 10) == -1) {
            throw std::runtime_error("Failed to listen on socket");
        }

        std::cout << "Echo server listening on port " << port << std::endl;
    }

    ~EchoServer() {
        close(server_fd);
    }

    void handleEvent(Handle handle) override {
        if (handle == server_fd) {
            acceptConnection();
        } else {
            echoData(handle);
        }
    }

private:
    void acceptConnection() {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            std::cerr << "Failed to accept connection" << std::endl;
            return;
        }

        std::cout << "Accepted connection from " << inet_ntoa(client_addr.sin_addr) << std::endl;

        reactor->registerHandler(client_fd, this);
    }

    void echoData(Handle handle) {
        char buffer[1024];
        ssize_t bytes_read = read(handle, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            write(handle, buffer, bytes_read);
        } else {
            reactor->removeHandler(handle);
            close(handle);
            std::cout << "Connection closed" << std::endl;
        }
    }

public:
    Handle& getServerHandle() {
        return server_fd;
    }

    void setReactor(Reactor* p_reactor) {
        this->reactor = p_reactor;
    }

private:
    Handle server_fd;
    Reactor* reactor;
};

int main() {
    try {
        Reactor reactor;

        EchoServer echoServer(8080);
        echoServer.setReactor(&reactor);

        reactor.registerHandler(echoServer.getServerHandle(), &echoServer);

        reactor.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}