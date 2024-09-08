#include <iostream>
#include <vector>
#include <list>
#include <chrono>

void sumArray(const std::vector<int>& array) {
    volatile int sum = 0;
    for (int value : array) {
        sum += value;
    }
}

void sumList(const std::list<int>& list) {
    volatile int sum = 0;
    for (int value : list) {
        sum += value;
    }
}

int main() {
    constexpr size_t size = 1000000;
    std::vector<int> array(size, 1);
    std::list<int> list(size, 1);

    auto start = std::chrono::high_resolution_clock::now();
    sumArray(array);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationArray = end - start;

    start = std::chrono::high_resolution_clock::now();
    sumList(list);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationList = end - start;

    std::cout << "Array sum time: " << durationArray.count() << " seconds" << std::endl;
    std::cout << "List sum time: " << durationList.count() << " seconds" << std::endl;

    return 0;
}