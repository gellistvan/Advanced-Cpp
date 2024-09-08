#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> data1(0);
std::atomic<int> data2(0);

void thread1() {
    data1.store(1, std::memory_order_seq_cst);
    data2.store(2, std::memory_order_seq_cst);
}

void thread2() {
    while (data2.load(std::memory_order_seq_cst) != 2);
    std::cout << "data1: " << data1.load(std::memory_order_seq_cst) << std::endl;
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();
    return 0;
}