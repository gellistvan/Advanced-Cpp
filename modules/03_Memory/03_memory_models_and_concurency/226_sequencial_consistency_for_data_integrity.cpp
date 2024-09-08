#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> sharedValue(0);
std::atomic<bool> ready(false);

void producer() {
    sharedValue.store(42, std::memory_order_seq_cst);
    ready.store(true, std::memory_order_seq_cst);
}

void consumer() {
    while (!ready.load(std::memory_order_seq_cst));
    std::cout << "Shared value: " << sharedValue.load(std::memory_order_seq_cst) << std::endl;
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}