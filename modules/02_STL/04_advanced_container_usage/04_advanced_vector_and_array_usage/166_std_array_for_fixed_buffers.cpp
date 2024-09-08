#include <iostream>
#include <array>
#include <algorithm>

int main() {
    std::array<char, 128> buffer;

    std::fill(buffer.begin(), buffer.end(), 0);

    std::string message = "Hello, World!";
    std::copy(message.begin(), message.end(), buffer.begin());

    std::cout << "Buffer contents: " << buffer.data() << std::endl;

    return 0;
}