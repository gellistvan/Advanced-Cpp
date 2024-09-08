#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> counter(0);

void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        asm volatile (
            "lock; incl %0"
            : "=m" (counter)
            : "m" (counter)
        );
    }
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}