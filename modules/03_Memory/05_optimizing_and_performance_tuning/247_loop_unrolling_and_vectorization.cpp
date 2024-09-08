#include <iostream>
#include <vector>
#include <immintrin.h>
#include <chrono>

void sumArray(const std::vector<int>& array) {
    __m256i sumVec1 = _mm256_setzero_si256();
    __m256i sumVec2 = _mm256_setzero_si256();
    size_t size = array.size();
    size_t i = 0;

    // Process 16 elements at a time using AVX
    for (; i + 16 <= size; i += 16) {
        __m256i dataVec1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&array[i]));
        __m256i dataVec2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&array[i + 8]));
        sumVec1 = _mm256_add_epi32(sumVec1, dataVec1);
        sumVec2 = _mm256_add_epi32(sumVec2, dataVec2);
    }

    // Horizontal sum of the SIMD vectors
    int sumArray[8];
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(sumArray), sumVec1);
    int sum = 0;
    for (int j = 0; j < 8; ++j) {
        sum += sumArray[j];
    }

    _mm256_storeu_si256(reinterpret_cast<__m256i*>(sumArray), sumVec2);
    for (int j = 0; j < 8; ++j) {
        sum += sumArray[j];
    }

    // Process remaining elements
    for (; i < size; ++i) {
        sum += array[i];
    }

    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    constexpr size_t size = 1000000;
    std::vector<int> array(size, 1);

    auto start = std::chrono::high_resolution_clock::now();
    sumArray(array);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    return 0;
}