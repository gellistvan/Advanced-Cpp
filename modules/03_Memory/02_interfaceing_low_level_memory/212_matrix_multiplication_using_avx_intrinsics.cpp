#include <iostream>
#include <immintrin.h> // Header file for AVX intrinsics

void exampleMatrixMultiplication() {
    alignas(32) float A[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    alignas(32) float B[8] = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    alignas(32) float C[8];

    // Load data into AVX registers
    __m256 vecA = _mm256_load_ps(A);
    __m256 vecB = _mm256_load_ps(B);

    // Perform element-wise multiplication
    __m256 vecC = _mm256_mul_ps(vecA, vecB);

    // Store the result back to memory
    _mm256_store_ps(C, vecC);

    // Print the result
    std::cout << "Result: ";
    for (float f : C) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
}

void comprehensiveAVXExample() {
    alignas(32) float A[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    alignas(32) float B[8] = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    alignas(32) float C[8];

    // Load data into AVX registers
    __m256 vecA = _mm256_load_ps(A); // Load A into vecA
    __m256 vecB = _mm256_load_ps(B); // Load B into vecB

    // Element-wise addition
    __m256 addResult = _mm256_add_ps(vecA, vecB);

    // Element-wise subtraction
    __m256 subResult = _mm256_sub_ps(vecA, vecB);

    // Element-wise multiplication
    __m256 mulResult = _mm256_mul_ps(vecA, vecB);

    // Element-wise division
    __m256 divResult = _mm256_div_ps(vecA, vecB);

    // Logical AND (bitwise AND)
    __m256 andResult = _mm256_and_ps(vecA, vecB);

    // Logical OR (bitwise OR)
    __m256 orResult = _mm256_or_ps(vecA, vecB);

    // Max and Min
    __m256 maxResult = _mm256_max_ps(vecA, vecB);
    __m256 minResult = _mm256_min_ps(vecA, vecB);

    // Square root of elements
    __m256 sqrtResult = _mm256_sqrt_ps(vecA);

    // Horizontal addition (pairs of elements added)
    __m256 haddResult = _mm256_hadd_ps(vecA, vecB);

    // Compare elements (greater than)
    __m256 cmpResult = _mm256_cmp_ps(vecA, vecB, _CMP_GT_OQ); // vecA > vecB

    // Store the result of the addition back to memory
    _mm256_store_ps(C, addResult);

    // Print the results
    std::cout << "Element-wise addition: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, subResult);
    std::cout << "Element-wise subtraction: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, mulResult);
    std::cout << "Element-wise multiplication: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, divResult);
    std::cout << "Element-wise division: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, andResult);
    std::cout << "Bitwise AND: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, orResult);
    std::cout << "Bitwise OR: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, maxResult);
    std::cout << "Max: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, minResult);
    std::cout << "Min: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, sqrtResult);
    std::cout << "Square root: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, haddResult);
    std::cout << "Horizontal addition: ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;

    _mm256_store_ps(C, cmpResult);
    std::cout << "Comparison (A > B): ";
    for (float f : C) std::cout << f << " ";
    std::cout << std::endl;
}

int main() {
    exampleMatrixMultiplication();
    comprehensiveAVXExample();
    return 0;
}