#include <iostream>



int main() {
    int A = 5;
    int * __restrict__ a {&A};
    int *  b {&A};

    int * __restrict__ c = static_cast<int* __restrict__>(b);


    std::cout << "Hello from hello_world_1.cpp!" << std::endl;
    return 0;
}
