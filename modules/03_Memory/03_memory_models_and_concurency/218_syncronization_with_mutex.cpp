#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;
int sharedData = 0;

void incrementData() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++sharedData;
    }
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementData);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final shared data value: " << sharedData << std::endl;
    return 0;
}