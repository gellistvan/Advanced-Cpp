#include <iostream>
#include <string>
#include <string_view>

std::string_view find_word(const std::string& str, std::string_view word) {
    size_t pos = str.find(word);
    if (pos != std::string::npos) {
        return std::string_view(str).substr(pos, word.size());
    }
    return std::string_view();
}

int main() {
    std::string text = "The quick brown fox jumps over the lazy dog";
    std::string_view word = "fox";
    
    std::string_view result = find_word(text, word);
    
    if (!result.empty()) {
        std::cout << "Found: " << result << std::endl;
    } else {
        std::cout << "Word not found" << std::endl;
    }

    return 0;
}