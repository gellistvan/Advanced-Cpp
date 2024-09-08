#include <iostream>
#include <vector>
#include <immintrin.h>
#include <chrono>

void sumArray(const std::vector<int>& array) {
    __m256i sumVec = _mm256_setzero_si256();
    size_t size = array.size();
    size_t i = 0;

    // Process 8 elements at a time using AVX
    for (; i + 8 <= size; i += 8) {
        __m256i dataVec = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&array[i]));
        sumVec = _mm256_add_epi32(sumVec, dataVec);
    }

    // Horizontal sum of the SIMD vector
    int sumArray[8];
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(sumArray), sumVec);
    int sum = 0;
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