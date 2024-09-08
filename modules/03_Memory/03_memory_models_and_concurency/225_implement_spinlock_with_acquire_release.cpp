#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class Spinlock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire));
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

Spinlock spinlock;
int sharedCounter = 0;

void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        spinlock.lock();
        ++sharedCounter;
        spinlock.unlock();
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

    std::cout << "Final counter value: " << sharedCounter << std::endl;
    return 0;
}