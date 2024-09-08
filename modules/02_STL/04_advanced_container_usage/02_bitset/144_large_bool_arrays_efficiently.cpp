#include <bitset>
#include <iostream>
#include <vector>
#include <random>

int main() {
    const int size = 1000000;
    std::bitset<size> bit_array;

    // Initialize bit_array with random values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < size; ++i) {
        bit_array[i] = dis(gen);
    }

    // Count the number of set bits
    std::cout << "Number of set bits: " << bit_array.count() << std::endl;

    return 0;
}