#include <iostream>
#include <vector>
#include <chrono>

void columnMajorAccess(const std::vector<std::vector<int>>& matrix) {
    int sum = 0;
    size_t N = matrix.size();
    for (size_t j = 0; j < N; ++j) {
        for (size_t i = 0; i < N; ++i) {
            sum += matrix[i][j];
        }
    }
    std::cout << "Sum (column-major): " << sum << std::endl;
}

void rowMajorAccess(const std::vector<std::vector<int>>& matrix) {
    int sum = 0;
    size_t N = matrix.size();
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            sum += matrix[i][j];
        }
    }
    std::cout << "Sum (row-major): " << sum << std::endl;
}

int main() {
    constexpr size_t N = 1024;
    std::vector<std::vector<int>> matrix(N, std::vector<int>(N, 1));

    auto start = std::chrono::high_resolution_clock::now();
    columnMajorAccess(matrix);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationColumnMajor = end - start;

    start = std::chrono::high_resolution_clock::now();
    rowMajorAccess(matrix);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationRowMajor = end - start;

    std::cout << "Column-major access time: " << durationColumnMajor.count() << " seconds" << std::endl;
    std::cout << "Row-major access time: " << durationRowMajor.count() << " seconds" << std::endl;

    return 0;
}