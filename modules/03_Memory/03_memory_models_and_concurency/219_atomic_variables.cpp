#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> atomicCounter(0);

void incrementAtomicCounter() {
    for (int i = 0; i < 1000; ++i) {
        atomicCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementAtomicCounter);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final atomic counter value: " << atomicCounter.load() << std::endl;
    return 0;
}