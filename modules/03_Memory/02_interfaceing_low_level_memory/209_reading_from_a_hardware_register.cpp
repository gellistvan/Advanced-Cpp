#include <iostream>
#include <cstdint>

uint64_t readTSC() {
    uint32_t low, high;
    asm volatile ("rdtsc"
                  : "=a" (low), "=d" (high)
                  : 
                  : );
    return (static_cast<uint64_t>(high) << 32) | low;
}

int main() {
    uint64_t tsc = readTSC();
    std::cout << "Time Stamp Counter: " << tsc << std::endl;
    return 0;
}