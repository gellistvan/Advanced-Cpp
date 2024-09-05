#include <iostream>

// Base case: no arguments to print
void print() {
    std::cout << "No more arguments." << std::endl;
}

// Recursive case: print the first argument and recurse
template<typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << std::endl;
    print(args...); // Recursively call print with the remaining arguments
}

int main() {
    print(1, 2.5, "Hello", 'A'); 
    // Output:
    // 1
    // 2.5
    // Hello
    // A
    // No more arguments.
    return 0;
}