#include <iostream>

void exampleBasicInlineAssembly() {
    int result;
    asm ("movl $42, %0"
         : "=r" (result) // Output operand
         :               // No input operands
         :               // No clobbers
    );

    std::cout << "Result: " << result << std::endl;
}

int main() {
    exampleBasicInlineAssembly();
    return 0;
}