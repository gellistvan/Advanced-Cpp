#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::pair<int, std::string>> vec;

    // Using push_back
    vec.push_back(std::make_pair(1, "one"));

    // Using emplace_back
    vec.emplace_back(2, "two");

    for (const auto& p : vec) {
        std::cout << p.first << ": " << p.second << std::endl;
    }

    return 0;
}