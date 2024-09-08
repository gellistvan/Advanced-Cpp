#include <iostream>
#include <immintrin.h>
#include <vector>

void applyGain(float* data, size_t size, float gain) {
    __m256 gainVec = _mm256_set1_ps(gain);
    size_t simdWidth = 8;
    size_t i = 0;

    for (; i + simdWidth <= size; i += simdWidth) {
        __m256 dataVec = _mm256_loadu_ps(&data[i]);
        __m256 resultVec = _mm256_mul_ps(dataVec, gainVec);
        _mm256_storeu_ps(&data[i], resultVec);
    }

    for (; i < size; ++i) {
        data[i] *= gain;
    }
}

int main() {
    std::vector<float> data(16);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = static_cast<float>(i);
    }

    applyGain(data.data(), data.size(), 1.5f);

    std::cout << "Transformed data: ";
    for (const auto& value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}