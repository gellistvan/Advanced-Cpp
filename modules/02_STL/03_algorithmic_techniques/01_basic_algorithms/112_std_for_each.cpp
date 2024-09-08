#include <algorithm>
#include <iostream>
#include <vector>

void print(int n) {
    std::cout << n << ' ';
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::cout << "Elements in vector: ";
    std::for_each(vec.begin(), vec.end(), print);
    std::cout << std::endl;

    return 0;
}