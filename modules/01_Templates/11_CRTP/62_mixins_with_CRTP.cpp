#include <iostream>

template <typename Derived>
class Printable {
public:
    void print() const {
        static_cast<const Derived*>(this)->print();
    }
};

class Data : public Printable<Data> {
public:
    void print() const {
        std::cout << "Data contents" << std::endl;
    }
};

class Logger : public Printable<Logger> {
public:
    void print() const {
        std::cout << "Logger contents" << std::endl;
    }
};

int main() {
    Data data;
    Logger logger;

    data.print();   // Output: Data contents
    logger.print(); // Output: Logger contents

    return 0;
}