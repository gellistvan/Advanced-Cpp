#include <iostream>
#include <array>

// Compile-time matrix multiplication
template<std::size_t N, std::size_t M, std::size_t P>
constexpr auto multiply(const std::array<std::array<int, M>, N>& a, const std::array<std::array<int, P>, M>& b) {
    std::array<std::array<int, P>, N> result = {};

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < P; ++j) {
            int sum = 0;
            for (std::size_t k = 0; k < M; ++k) {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

int main() {
    constexpr std::array<std::array<int, 2>, 2> a = {{{1, 2}, {3, 4}}};
    constexpr std::array<std::array<int, 2>, 2> b = {{{5, 6}, {7, 8}}};
    constexpr auto result = multiply(a, b);

    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    // Output:
    // 19 22
    // 43 50

    return 0;
}