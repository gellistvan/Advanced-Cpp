#include <iostream>
#include <array>
#include <cstring>

void exampleCpuid() {
    std::array<int, 4> cpuInfo;
    int functionId = 0; // CPUID function 0: Get vendor ID

    asm volatile ("cpuid"
                  : "=a" (cpuInfo[0]), "=b" (cpuInfo[1]), "=c" (cpuInfo[2]), "=d" (cpuInfo[3])
                  : "a" (functionId)
                  : );

    char vendor[13];
    std::memcpy(vendor, &cpuInfo[1], 4);
    std::memcpy(vendor + 4, &cpuInfo[3], 4);
    std::memcpy(vendor + 8, &cpuInfo[2], 4);
    vendor[12] = '\0';

    std::cout << "CPU Vendor: " << vendor << std::endl;
}

int main() {
    exampleCpuid();
    return 0;
}