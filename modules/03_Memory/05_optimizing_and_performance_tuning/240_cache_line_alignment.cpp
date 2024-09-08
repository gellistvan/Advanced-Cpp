#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

constexpr size_t CACHE_LINE_SIZE = 64;

struct alignas(CACHE_LINE_SIZE) PaddedCounter {
    std::atomic<int> counter;
};

void incrementCounter(PaddedCounter& counter) {
    for (int i = 0; i < 1000000; ++i) {
        ++counter.counter;
    }
}

int main() {
    PaddedCounter counter1;
    PaddedCounter counter2;

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(incrementCounter, std::ref(counter1));
    std::thread t2(incrementCounter, std::ref(counter2));

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    std::cout << "Counter1: " << counter1.counter << ", Counter2: " << counter2.counter << std::endl;

    return 0;
}