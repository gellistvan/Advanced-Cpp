#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 2, 3, 3, 3, 4, 5};

    int count = std::count(vec.begin(), vec.end(), 3);
    std::cout << "Number of 3s: " << count << std::endl;

    return 0;
}