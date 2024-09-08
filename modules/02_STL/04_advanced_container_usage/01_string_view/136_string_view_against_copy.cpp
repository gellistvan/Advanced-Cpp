#include <iostream>
#include <string_view>

void print_string_view(std::string_view str_view) {
    std::cout << str_view << std::endl;
}

int main() {
    std::string str = "Hello, World!";
    print_string_view(str); // No copy is made

    const char* c_str = "C-Style String";
    print_string_view(c_str); // No copy is made

    return 0;
}