#include <iostream>
#include <atomic>
#include <thread>

std::atomic<bool> ready(false);  // Shared atomic flag to indicate readiness
std::atomic<int> data(0);        // Shared atomic data

// Producer thread writes data and signals readiness
void producer() {
    // Store the data (relaxed memory order - no synchronization required here)
    data.store(42, std::memory_order_relaxed);

    // Signal the consumer that data is ready (release memory order)
    // memory_order_release ensures that all prior writes (data) are visible
    // to other threads before this write (ready = true)
    ready.store(true, std::memory_order_release);
}

// Consumer thread waits for the ready flag, then reads the data
void consumer() {
    // Spin-wait until the ready flag is set to true
    // memory_order_acquire ensures that the read of 'ready' synchronizes with
    // the release of 'ready' in producer, meaning all previous writes in producer
    // (like data.store(42)) are visible to this thread
    while (!ready.load(std::memory_order_acquire));

    // Once ready is true, read the data (relaxed order is fine here since acquire-release
    // synchronization already guarantees visibility of previous writes)
    std::cout << "Data: " << data.load(std::memory_order_relaxed) << std::endl;
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
