#include <iostream>
#include <vector>
#include <chrono>

void sumArray(const std::vector<int>& array) {
    int sum = 0;
    size_t size = array.size();

#pragma omp simd
    for (size_t i = 0; i < size; ++i) {
        sum += array[i];
    }

    std::cout << "Sum: " << sum << std::endl;
}

void sumArrayVectorized(const std::vector<int>& array) {
    int sum = 0;
#pragma omp simd reduction(+:sum)
    for (size_t i = 0; i < array.size(); ++i) {
        sum += array[i];
    }
    std::cout << "Sum (vectorized): " << sum << std::endl;
}


int main() {
    constexpr size_t size = 1000000;
    std::vector<int> array(size, 1);
    {
        auto start = std::chrono::high_resolution_clock::now();
        sumArray(array);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    }
    {
        auto start = std::chrono::high_resolution_clock::now();
        sumArrayVectorized(array);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    }

    return 0;
}