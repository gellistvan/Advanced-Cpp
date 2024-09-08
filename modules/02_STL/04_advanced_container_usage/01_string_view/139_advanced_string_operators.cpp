#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<std::string_view> split_string(std::string_view str, char delimiter) {
    std::vector<std::string_view> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}

int main() {
    std::string text = "Hello,World,This,Is,C++";
    std::vector<std::string_view> words = split_string(text, ',');

    for (const auto& word : words) {
        std::cout << word << std::endl;
    }

    return 0;
}