#include <bitset>
#include <iostream>

int main() {
    std::bitset<8> bits("11001100");

    std::cout << "Initial bitset: " << bits << std::endl;
    std::cout << "Number of set bits: " << bits.count() << std::endl;

    bits.flip();
    std::cout << "Flipped bitset: " << bits << std::endl;

    bits.set(0);
    std::cout << "Set bit 0: " << bits << std::endl;

    bits.reset(0);
    std::cout << "Reset bit 0: " << bits << std::endl;

    return 0;
}