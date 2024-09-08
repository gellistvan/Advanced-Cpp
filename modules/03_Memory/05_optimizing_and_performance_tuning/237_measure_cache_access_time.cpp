#include <iostream>
#include <vector>
#include <chrono>

void measureCacheAccessTime(int* array, size_t size) {
    volatile int sum = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < size; i += 64 / sizeof(int)) {
        sum += array[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}

int main() {
    constexpr size_t arraySize = 1024 * 1024 * 16; // 16 million integers (~64 MB)
    std::vector<int> array(arraySize, 1);

    measureCacheAccessTime(array.data(), arraySize);

    return 0;
}