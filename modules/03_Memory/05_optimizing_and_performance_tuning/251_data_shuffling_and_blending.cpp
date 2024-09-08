#include <iostream>
#include <immintrin.h> // AVX intrinsics

void avxShuffleExample() {
    float data[8] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f};
    float result[8];

    // Load data into AVX register
    __m256 vec = _mm256_loadu_ps(data);

    // Shuffle the data (swap the first half with the second half)
    __m256 shuffledVec = _mm256_permute2f128_ps(vec, vec, 1);

    // Store the result
    _mm256_storeu_ps(result, shuffledVec);

    // Print the result
    std::cout << "Shuffled result: ";
    for (float f : result) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
}

int main() {
    avxShuffleExample();
    return 0;
}