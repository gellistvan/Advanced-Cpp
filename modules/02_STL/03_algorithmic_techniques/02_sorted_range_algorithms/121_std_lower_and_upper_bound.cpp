#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 2, 3, 4, 5};
    
    int key = 2;
    auto it = std::lower_bound(vec.begin(), vec.end(), key);
    
    if (it != vec.end()) {
        std::cout << "Lower bound of " << key << " is at position: " << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << key << " is greater than all elements." << std::endl;
    }

    it = std::upper_bound(vec.begin(), vec.end(), key);

    if (it != vec.end()) {
        std::cout << "Upper bound of " << key << " is at position: " << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << key << " is greater than all elements." << std::endl;
    }

    return 0;
}