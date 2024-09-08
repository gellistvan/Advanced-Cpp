#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    int key = 3;
    bool found = std::binary_search(vec.begin(), vec.end(), key);
    
    if (found) {
        std::cout << key << " is in the vector." << std::endl;
    } else {
        std::cout << key << " is not in the vector." << std::endl;
    }

    return 0;
}