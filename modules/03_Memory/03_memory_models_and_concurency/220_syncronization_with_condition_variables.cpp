#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <queue>
#include <atomic>

// Shared resources
std::mutex mtx;
std::condition_variable cv;
std::queue<int> dataQueue;  // Queue to hold produced data
std::atomic<bool> done(false);  // Flag to indicate when production is done
bool ready = false;  // Signifies when new data is available

const int max_items = 10;  // Number of items to produce

// Producer function to generate data
void producer() {
    for (int i = 1; i <= max_items; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(i);
            ready = true;
            std::cout << "Produced: " << i << std::endl;
        }
        cv.notify_all();  // Notify all consumers that new data is available
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work
    }

    // Indicate that production is done
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
        ready = true;  // This is important to wake up all consumers after the work is done
    }
    cv.notify_all();  // Wake up all consumers to finish
}

// Consumer function to consume data
void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait for new data to be ready or production to be finished
        cv.wait(lock, [] { return ready; });

        // If production is done and no more data, exit the loop
        if (done && dataQueue.empty()) {
            break;
        }

        // Consume data if available
        if (!dataQueue.empty()) {
            int data = dataQueue.front();
            dataQueue.pop();
            ready = !dataQueue.empty();  // If there's more data, keep ready true
            std::cout << "Consumer " << id << " consumed: " << data << std::endl;
        }
    }
}

int main() {
    // Create threads for one producer and multiple consumers
    std::thread prodThread(producer);
    std::vector<std::thread> consumerThreads;
    const int numConsumers = 3;

    // Launch consumer threads
    for (int i = 0; i < numConsumers; ++i) {
        consumerThreads.emplace_back(consumer, i + 1);
    }

    // Wait for producer and consumer threads to finish
    prodThread.join();
    for (auto& t : consumerThreads) {
        t.join();
    }

    return 0;
}
