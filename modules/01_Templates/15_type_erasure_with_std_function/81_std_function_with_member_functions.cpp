#include <functional>
#include <iostream>
#include <string>

class Printer {
public:
    void print(const std::string& message) const {
        std::cout << "Printer: " << message << std::endl;
    }
};

int main() {
    Printer printer;

    // Store a member function pointer in std::function
    std::function<void(const Printer&, const std::string&)> func = &Printer::print;

    // Invoke the member function on the printer object
    func(printer, "Hello, Member Function!"); // Output: Printer: Hello, Member Function!

    return 0;
}