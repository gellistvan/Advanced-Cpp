#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {2, 4};
    
    bool result = std::includes(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
    
    if (result) {
        std::cout << "vec1 includes all elements of vec2." << std::endl;
    } else {
        std::cout << "vec1 does not include all elements of vec2." << std::endl;
    }

    return 0;
}