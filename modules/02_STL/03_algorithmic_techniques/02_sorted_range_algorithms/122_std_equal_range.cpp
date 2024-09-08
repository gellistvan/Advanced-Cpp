#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 2, 3, 4, 5};
    
    int key = 2;
    auto range = std::equal_range(vec.begin(), vec.end(), key);
    
    std::cout << "Equal range of " << key << " is from position: " 
              << std::distance(vec.begin(), range.first) << " to position: " 
              << std::distance(vec.begin(), range.second) << std::endl;

    return 0;
}