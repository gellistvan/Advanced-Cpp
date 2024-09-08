#include <iostream>
#include <immintrin.h>
#include <vector>

void avxHandleRemainders(const std::vector<float>& input, std::vector<float>& output) {
    size_t size = input.size();
    size_t i = 0;

    // Process complete SIMD registers
    for (; i + 8 <= size; i += 8) {
        __m256 vec = _mm256_loadu_ps(&input[i]);
        __m256 vecResult = _mm256_add_ps(vec, _mm256_set1_ps(1.0f));
        _mm256_storeu_ps(&output[i], vecResult);
    }

    // Handle remaining elements
    for (; i < size; ++i) {
        output[i] = input[i] + 1.0f;
    }
}

int main() {
    constexpr size_t size = 20;
    std::vector<float> input(size, 1.0f);
    std::vector<float> output(size, 0.0f);

    avxHandleRemainders(input, output);

    std::cout << "Output: ";
    for (float value : output) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}