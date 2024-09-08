#include <iostream>
#include <vector>
#include <chrono>

void sumArray(const std::vector<int>& array) {
    int sum = 0;
    size_t size = array.size();

    // Unrolled loop
    for (size_t i = 0; i < size; i += 4) {
        sum += array[i];
        if (i + 1 < size) sum += array[i + 1];
        if (i + 2 < size) sum += array[i + 2];
        if (i + 3 < size) sum += array[i + 3];
    }

    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    constexpr size_t size = 1000000;
    std::vector<int> array(size, 1);

    auto start = std::chrono::high_resolution_clock::now();
    sumArray(array);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    return 0;
}