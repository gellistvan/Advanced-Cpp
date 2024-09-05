#include <iostream>

template <typename Derived>
class Logger {
public:
    void log(const std::string& message) const {
        static_cast<const Derived*>(this)->logImpl(message);
    }
};

class FileLogger : public Logger<FileLogger> {
public:
    void logImpl(const std::string& message) const {
        std::cout << "File log: " << message << std::endl;
    }
};

class ConsoleLogger : public Logger<ConsoleLogger> {
public:
    void logImpl(const std::string& message) const {
        std::cout << "Console log: " << message << std::endl;
    }
};

int main() {
    FileLogger fileLogger;
    ConsoleLogger consoleLogger;

    fileLogger.log("This is a file log message."); // Output: File log: This is a file log message.
    consoleLogger.log("This is a console log message."); // Output: Console log: This is a console log message.

    return 0;
}