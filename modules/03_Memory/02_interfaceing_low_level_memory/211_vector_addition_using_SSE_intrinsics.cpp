#include <iostream>
#include <xmmintrin.h> // Header file for SSE intrinsics

void exampleVectorAddition() {
    alignas(16) float a[4] = {1.0, 2.0, 3.0, 4.0};
    alignas(16) float b[4] = {5.0, 6.0, 7.0, 8.0};
    alignas(16) float c[4];

    // Load data into SSE registers
    __m128 vecA = _mm_load_ps(a);
    __m128 vecB = _mm_load_ps(b);

    // Perform vector addition
    __m128 vecC = _mm_add_ps(vecA, vecB);

    // Store the result back to memory
    _mm_store_ps(c, vecC);

    // Print the result
    std::cout << "Result: ";
    for (float f : c) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
}

void comprehensiveSSEExample() {
    alignas(16) float a[4] = {1.0, 2.0, 3.0, 4.0};
    alignas(16) float b[4] = {5.0, 6.0, 7.0, 8.0};
    alignas(16) float c[4];

    // Load data into SSE registers
    __m128 vecA = _mm_load_ps(a);  // Load a into vecA
    __m128 vecB = _mm_load_ps(b);  // Load b into vecB

    // Element-wise addition
    __m128 addResult = _mm_add_ps(vecA, vecB);

    // Element-wise subtraction
    __m128 subResult = _mm_sub_ps(vecA, vecB);

    // Element-wise multiplication
    __m128 mulResult = _mm_mul_ps(vecA, vecB);

    // Element-wise division
    __m128 divResult = _mm_div_ps(vecA, vecB);

    // Square root of elements
    __m128 sqrtResult = _mm_sqrt_ps(vecA);

    // Logical AND (bitwise AND)
    __m128 andResult = _mm_and_ps(vecA, vecB);

    // Logical OR (bitwise OR)
    __m128 orResult = _mm_or_ps(vecA, vecB);

    // Logical XOR (bitwise XOR)
    __m128 xorResult = _mm_xor_ps(vecA, vecB);

    // Max and Min
    __m128 maxResult = _mm_max_ps(vecA, vecB);
    __m128 minResult = _mm_min_ps(vecA, vecB);

    // Horizontal addition (pairs of elements added)
    // __m128 haddResult = _mm_hadd_ps(vecA, vecB); //SSE3 only!

    // Compare elements (greater than)
    __m128 cmpResult = _mm_cmpgt_ps(vecA, vecB);

    // Store and print results
    auto printSSEResult = [](const char* name, const __m128& vec) {
        alignas(16) float res[4];
        _mm_store_ps(res, vec);
        std::cout << name << ": ";
        for (float f : res) std::cout << f << " ";
        std::cout << std::endl;
    };

    printSSEResult("Addition", addResult);
    printSSEResult("Subtraction", subResult);
    printSSEResult("Multiplication", mulResult);
    printSSEResult("Division", divResult);
    printSSEResult("Square Root", sqrtResult);
    printSSEResult("Bitwise AND", andResult);
    printSSEResult("Bitwise OR", orResult);
    printSSEResult("Bitwise XOR", xorResult);
    printSSEResult("Max", maxResult);
    printSSEResult("Min", minResult);
    // printSSEResult("Horizontal Addition", haddResult);
    printSSEResult("Comparison (A > B)", cmpResult);
}

int main() {
    exampleVectorAddition();
    comprehensiveSSEExample();
    return 0;
}