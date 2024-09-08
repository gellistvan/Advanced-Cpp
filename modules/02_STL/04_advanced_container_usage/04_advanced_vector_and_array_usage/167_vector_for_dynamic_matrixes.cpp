#include <iostream>
#include <vector>

int main() {
    int rows = 3;
    int cols = 3;
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    // Fill matrix with values
    int value = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = value++;
        }
    }

    // Print matrix
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}