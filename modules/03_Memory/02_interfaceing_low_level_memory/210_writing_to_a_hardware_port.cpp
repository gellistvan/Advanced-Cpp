#include <iostream>

void writePort(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1"
                  :
                  : "a" (value), "Nd" (port)
                  : );
}

int main() {
    uint16_t port = 0x80; // Example port number
    uint8_t value = 0xFF; // Example value to write

    writePort(port, value);
    std::cout << "Value written to port." << std::endl;
    return 0;
}