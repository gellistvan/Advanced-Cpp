#include <iostream>

void exampleInlineAssemblyWithInput() {
    int x = 10;
    int y = 20;
    int result;

    asm ("addl %2, %1\n\t"
         "movl %1, %0"
         : "=r" (result) // Output operand
         : "r" (x), "r" (y) // Input operands
         :                 // No clobbers
    );

    std::cout << "Result: " << result << std::endl;
}

int main() {
    exampleInlineAssemblyWithInput();
    return 0;
}