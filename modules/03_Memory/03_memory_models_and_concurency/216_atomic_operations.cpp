#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <cassert>

// Using an atomic counter initialized to 0
std::atomic<int> counter(0);

// Function to increment the counter using atomic fetch_add
void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        // Using relaxed memory ordering (no synchronization between threads)
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

// Function to decrement the counter using atomic fetch_sub
void decrementCounter() {
    for (int i = 0; i < 500; ++i) {
        // Relaxed memory order still, only affects counter, no synchronization
        counter.fetch_sub(1, std::memory_order_relaxed);
    }
}

// Function to use compare_exchange_strong to update the counter
void compareAndSwapCounter() {
    int expected = 5000; // Assume counter should be 5000 initially
    int newValue = 10000;
    // Attempt to atomically update the counter to 10000 if it's still 5000
    if (counter.compare_exchange_strong(expected, newValue, std::memory_order_acq_rel)) {
        std::cout << "Successfully updated counter to " << newValue << std::endl;
    } else {
        std::cout << "Compare and swap failed, counter is " << counter.load() << std::endl;
    }
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    // Launch threads to increment the counter
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter);
    }

    // Launch some threads to decrement the counter
    for (int i = 0; i < numThreads / 2; ++i) {
        threads.emplace_back(decrementCounter);
    }

    // Wait for all increment and decrement threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // At this point, the counter should have been incremented by 10 * 1000 = 10000
    // and decremented by 5 * 500 = 2500, so we expect the value to be 7500.
    std::cout << "Counter value after increments and decrements: " << counter.load() << std::endl;

    // Now demonstrate compare and swap (CAS)
    compareAndSwapCounter();

    // Final value check
    int finalValue = counter.load(std::memory_order_acquire);
    std::cout << "Final counter value: " << finalValue << std::endl;

    // Optional assertion for correctness
    assert(finalValue >= 7500 && "Final value should be greater than or equal to 7500");

    return 0;
}
