#include <iostream>
#include <string>
#include <string_view>

bool contains(std::string_view str, std::string_view substr) {
    return str.find(substr) != std::string::npos;
}

int main() {
    std::string text = "The quick brown fox jumps over the lazy dog";
    std::string_view search_str = "fox";

    if (contains(text, search_str)) {
        std::cout << "Found!" << std::endl;
    } else {
        std::cout << "Not found!" << std::endl;
    }

    return 0;
}