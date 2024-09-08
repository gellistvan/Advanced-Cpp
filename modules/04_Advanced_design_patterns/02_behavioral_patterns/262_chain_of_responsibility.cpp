#include <memory>
#include <string>
#include <iostream>

class Handler {
public:
    virtual ~Handler() = default;

    void setNext(std::shared_ptr<Handler> nextHandler) {
        next = nextHandler;
    }

    virtual void handleRequest(const std::string& message, int level) {
        if (next) {
            next->handleRequest(message, level);
        }
    }

protected:
    std::shared_ptr<Handler> next;
};

class ConsoleLogger : public Handler {
public:
    ConsoleLogger(int logLevel) : level(logLevel) {}

    void handleRequest(const std::string& message, int level) override {
        if (this->level <= level) {
            std::cout << "ConsoleLogger: " << message << std::endl;
        }
        Handler::handleRequest(message, level);
    }

private:
    int level;
};

class FileLogger : public Handler {
public:
    FileLogger(int logLevel) : level(logLevel) {}

    void handleRequest(const std::string& message, int level) override {
        if (this->level <= level) {
            // For simplicity, we'll just print to console instead of writing to a file
            std::cout << "FileLogger: " << message << std::endl;
        }
        Handler::handleRequest(message, level);
    }

private:
    int level;
};

class EmailLogger : public Handler {
public:
    EmailLogger(int logLevel) : level(logLevel) {}

    void handleRequest(const std::string& message, int level) override {
        if (this->level <= level) {
            // For simplicity, we'll just print to console instead of sending an email
            std::cout << "EmailLogger: " << message << std::endl;
        }
        Handler::handleRequest(message, level);
    }

private:
    int level;
};


int main() {
    std::shared_ptr<Handler> consoleLogger = std::make_shared<ConsoleLogger>(1);
    std::shared_ptr<Handler> fileLogger = std::make_shared<FileLogger>(2);
    std::shared_ptr<Handler> emailLogger = std::make_shared<EmailLogger>(3);

    consoleLogger->setNext(fileLogger);
    fileLogger->setNext(emailLogger);

    std::cout << "Sending log message with severity 1 (INFO):" << std::endl;
    consoleLogger->handleRequest("This is an information message.", 1);

    std::cout << "\nSending log message with severity 2 (WARNING):" << std::endl;
    consoleLogger->handleRequest("This is a warning message.", 2);

    std::cout << "\nSending log message with severity 3 (ERROR):" << std::endl;
    consoleLogger->handleRequest("This is an error message.", 3);

    return 0;
}