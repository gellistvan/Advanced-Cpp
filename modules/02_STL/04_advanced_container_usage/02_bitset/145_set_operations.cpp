#include <bitset>
#include <iostream>

int main() {
    std::bitset<8> set1("11001010");
    std::bitset<8> set2("10101011");

    std::bitset<8> union_set = set1 | set2;
    std::bitset<8> intersection_set = set1 & set2;
    std::bitset<8> difference_set = set1 ^ set2;

    std::cout << "Set 1: " << set1 << std::endl;
    std::cout << "Set 2: " << set2 << std::endl;
    std::cout << "Union: " << union_set << std::endl;
    std::cout << "Intersection: " << intersection_set << std::endl;
    std::cout << "Difference: " << difference_set << std::endl;

    return 0;
}