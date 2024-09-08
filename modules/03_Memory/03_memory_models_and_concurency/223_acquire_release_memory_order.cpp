#include <iostream>
#include <atomic>
#include <thread>

std::atomic<bool> flag(false);
std::atomic<int> sharedData(0);

void producer() {
    sharedData.store(42, std::memory_order_relaxed);
    flag.store(true, std::memory_order_release);
}

void consumer() {
    while (!flag.load(std::memory_order_acquire));
    std::cout << "Shared data: " << sharedData.load(std::memory_order_relaxed) << std::endl;
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}