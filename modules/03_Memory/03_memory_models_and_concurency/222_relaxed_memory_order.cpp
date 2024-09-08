#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> relaxedCounter(0);

void incrementRelaxedCounter() {
    for (int i = 0; i < 1000; ++i) {
        relaxedCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementRelaxedCounter);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final relaxed counter value: " << relaxedCounter.load(std::memory_order_relaxed) << std::endl;
    return 0;
}