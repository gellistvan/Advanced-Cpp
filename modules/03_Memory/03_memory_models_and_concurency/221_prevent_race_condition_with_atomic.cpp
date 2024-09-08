#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> sharedCounter(0);

void safeIncrement() {
    for (int i = 0; i < 1000; ++i) {
        sharedCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(safeIncrement);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << sharedCounter.load() << std::endl;
    return 0;
}