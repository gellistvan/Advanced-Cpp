#include <iostream>
#include <immintrin.h>
#include <vector>

void avxAlignedExample() {
    // Allocate aligned memory
    float* data = (float*)_mm_malloc(8 * sizeof(float), 32);

    // Initialize data
    for (int i = 0; i < 8; ++i) {
        data[i] = static_cast<float>(i);
    }

    // Load data into AVX register
    __m256 vec = _mm256_load_ps(data);

    // Perform some operation (e.g., adding a constant)
    __m256 vecResult = _mm256_add_ps(vec, _mm256_set1_ps(1.0f));

    // Store the result
    _mm256_store_ps(data, vecResult);

    // Print the result
    std::cout << "Aligned result: ";
    for (int i = 0; i < 8; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    // Free aligned memory
    _mm_free(data);
}

int main() {
    avxAlignedExample();
    return 0;
}