#include <iostream>
#include <immintrin.h>
#include <cstring>

void simdCopy(float* dest, const float* src, size_t count) {
    size_t simdWidth = 8; // AVX processes 8 floats at a time
    size_t i = 0;

    for (; i + simdWidth <= count; i += simdWidth) {
        __m256 data = _mm256_loadu_ps(&src[i]);
        _mm256_storeu_ps(&dest[i], data);
    }

    // Copy remaining elements
    for (; i < count; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    constexpr size_t size = 16;
    float src[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    float dest[size];

    simdCopy(dest, src, size);

    std::cout << "Copied data: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << dest[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}