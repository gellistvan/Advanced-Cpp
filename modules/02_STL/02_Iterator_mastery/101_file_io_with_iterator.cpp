//
// Created by István on 2024. 09. 08..
//
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string path {"/tmp/file.txt"};

    std::ofstream out_file(path);
    if (!out_file) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::copy(vec.begin(), vec.end(),
              std::ostream_iterator<int>(out_file, " "));
    out_file << std::endl;
    out_file.close();

    std::ifstream in_file(path);
    if (!in_file) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::vector<int> vec2;
    std::copy(std::istream_iterator<int>(in_file),
              std::istream_iterator<int>(),
              std::back_inserter(vec));

    std::cout << "File contents: ";
    for (const auto& val : vec2) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}