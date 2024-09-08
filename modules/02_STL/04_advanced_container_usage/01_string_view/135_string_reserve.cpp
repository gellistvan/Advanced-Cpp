#include <iostream>
#include <string>

int main() {
    std::string result;
    result.reserve(50); // Reserve enough memory to avoid reallocations

    for (int i = 0; i < 10; ++i) {
        result += "Hello ";
    }

    std::cout << result << std::endl;
    return 0;
}