#include <iostream>
#include <string_view>

int main() {
    std::string str = "Hello, World!";
    std::string_view view = str;

    std::string_view hello = view.substr(0, 5);
    std::string_view world = view.substr(7, 5);

    std::cout << "Hello: " << hello << std::endl;
    std::cout << "World: " << world << std::endl;

    return 0;
}