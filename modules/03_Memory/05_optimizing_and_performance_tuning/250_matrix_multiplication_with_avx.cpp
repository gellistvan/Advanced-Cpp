#include <iostream>
#include <immintrin.h> // AVX intrinsics

void avxMatrixMultiply(const float* A, const float* B, float* C, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            __m256 vecC = _mm256_setzero_ps();
            for (size_t k = 0; k < N; k += 8) {
                __m256 vecA = _mm256_loadu_ps(&A[i * N + k]);
                __m256 vecB = _mm256_loadu_ps(&B[k * N + j]);
                vecC = _mm256_fmadd_ps(vecA, vecB, vecC);
            }
            // Sum the elements of vecC and store in C[i * N + j]
            float temp[8];
            _mm256_storeu_ps(temp, vecC);
            C[i * N + j] = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];
        }
    }
}

int main() {
    constexpr size_t N = 8;
    float A[N * N] = { /* Initialize with appropriate values */ };
    float B[N * N] = { /* Initialize with appropriate values */ };
    float C[N * N] = {0};

    avxMatrixMultiply(A, B, C, N);

    std::cout << "Result matrix C: " << std::endl;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cout << C[i * N + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}