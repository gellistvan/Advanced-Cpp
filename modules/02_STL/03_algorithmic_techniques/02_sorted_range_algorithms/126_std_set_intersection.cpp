#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {2, 3, 4};
    std::vector<int> result;
    
    std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(result));
    
    std::cout << "Intersection of vec1 and vec2: ";
    for (const auto& val : result) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}