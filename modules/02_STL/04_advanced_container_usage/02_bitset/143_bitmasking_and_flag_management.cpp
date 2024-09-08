#include <bitset>
#include <iostream>

const int FLAG_A = 0;
const int FLAG_B = 1;
const int FLAG_C = 2;

int main() {
    std::bitset<8> flags;

    // Set flags
    flags.set(FLAG_A);
    flags.set(FLAG_B);

    std::cout << "Flags: " << flags << std::endl;

    // Check flags
    if (flags.test(FLAG_A)) {
        std::cout << "Flag A is set" << std::endl;
    }

    if (flags.test(FLAG_C)) {
        std::cout << "Flag C is set" << std::endl;
    } else {
        std::cout << "Flag C is not set" << std::endl;
    }

    // Reset flag
    flags.reset(FLAG_A);
    std::cout << "Flags after resetting FLAG_A: " << flags << std::endl;

    return 0;
}