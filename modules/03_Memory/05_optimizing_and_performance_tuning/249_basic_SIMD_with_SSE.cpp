#include <iostream>
#include <xmmintrin.h> // SSE intrinsics

void sseExample() {
    // Initialize data
    float dataA[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    float dataB[4] = {5.0f, 6.0f, 7.0f, 8.0f};
    float result[4];

    // Load data into SSE registers
    __m128 vecA = _mm_loadu_ps(dataA);
    __m128 vecB = _mm_loadu_ps(dataB);

    // Perform addition
    __m128 vecResult = _mm_add_ps(vecA, vecB);

    // Store the result
    _mm_storeu_ps(result, vecResult);

    // Print the result
    std::cout << "Result: ";
    for (float f : result) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
}

int main() {
    sseExample();
    return 0;
}