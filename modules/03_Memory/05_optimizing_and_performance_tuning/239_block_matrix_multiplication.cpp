#include <iostream>
#include <vector>
#include <chrono>

void blockMatrixMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, size_t blockSize) {
    size_t N = A.size();
    for (size_t i = 0; i < N; i += blockSize) {
        for (size_t j = 0; j < N; j += blockSize) {
            for (size_t k = 0; k < N; k += blockSize) {
                for (size_t ii = i; ii < i + blockSize && ii < N; ++ii) {
                    for (size_t jj = j; jj < j + blockSize && jj < N; ++jj) {
                        int sum = 0;
                        for (size_t kk = k; kk < k + blockSize && kk < N; ++kk) {
                            sum += A[ii][kk] * B[kk][jj];
                        }
                        C[ii][jj] += sum;
                    }
                }
            }
        }
    }
}

int main() {
    constexpr size_t N = 512;
    constexpr size_t blockSize = 64;
    std::vector<std::vector<int>> A(N, std::vector<int>(N, 1));
    std::vector<std::vector<int>> B(N, std::vector<int>(N, 2));
    std::vector<std::vector<int>> C(N, std::vector<int>(N, 0));

    auto start = std::chrono::high_resolution_clock::now();

    blockMatrixMultiply(A, B, C, blockSize);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}