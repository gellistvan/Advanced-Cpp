#include <iostream>
#include <cstring>

// General template for finding the maximum of two values
template<typename T>
T Max(T a, T b) {
    return (a > b) ? a : b;
}

// Full specialization for const char* to compare C-style strings
template<>
const char* Max<const char*>(const char* a, const char* b) {
    return (std::strcmp(a, b) > 0) ? a : b;
}

int main() {
    int x = 10, y = 20;
    std::cout << "Max of " << x << " and " << y << " is " << Max(x, y) << std::endl;

    const char* str1 = "Hello";
    const char* str2 = "World";
    std::cout << "Max of \"" << str1 << "\" and \"" << str2 << "\" is \"" << Max(str1, str2) << "\"" << std::endl;

    return 0;
}