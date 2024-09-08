#include <bitset>
#include <iostream>

const int BITSET_SIZE = 64

;

int main() {
    std::bitset<BITSET_SIZE> num1("1100"); // 12 in binary
    std::bitset<BITSET_SIZE> num2("1010"); // 10 in binary

    std::bitset<BITSET_SIZE> sum = num1 ^ num2; // Binary addition without carry
    std::bitset<BITSET_SIZE> carry = num1 & num2; // Carry bits

    // Adjust carry
    carry <<= 1;

    std::cout << "Num1: " << num1 << std::endl;
    std::cout << "Num2: " << num2 << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Carry: " << carry << std::endl;

    return 0;
}