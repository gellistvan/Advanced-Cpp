#include <iostream>
#include <immintrin.h> // AVX intrinsics

void avxBlendExample() {
    float dataA[8] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f};
    float dataB[8] = {8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f};
    float result[8];

    // Load data into AVX registers
    __m256 vecA = _mm256_loadu_ps(dataA);
    __m256 vecB = _mm256_loadu_ps(dataB);

    // Blend the data (take the first four elements from vecA and the last four from vecB)
    __m256 blendedVec = _mm256_blend_ps(vecA, vecB, 0xF0);

    // Store the result
    _mm256_storeu_ps(result, blendedVec);

    // Print the result
    std::cout << "Blended result: ";
    for (float f : result) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
}

int main() {
    avxBlendExample();
    return 0;
}