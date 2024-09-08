#include <iostream>
#include <string_view>

std::string_view dangling_substring() {
    std::string str = "Temporary String";
    return std::string_view(str).substr(0, 9); // Dangling reference -> undefined behavior!
}

std::string_view get_substring() {
    std::string str = "Temporary String";
    return str.substr(0, 9); // OK
}

int main() {
    std::string_view view = get_substring();
    std::cout << view << std::endl;
    return 0;
}