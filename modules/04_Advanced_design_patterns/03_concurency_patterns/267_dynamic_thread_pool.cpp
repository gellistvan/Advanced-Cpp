#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <condition_variable>
#include <chrono>
#include <functional>
#include <queue>

class DynamicThreadPool {
public:
    DynamicThreadPool(size_t minThreads, size_t maxThreads)
        : minThreads(minThreads), maxThreads(maxThreads), stop(false) {
        for (size_t i = 0; i < minThreads; ++i) {
            workers.emplace_back(&DynamicThreadPool::worker, this);
        }
    }

    ~DynamicThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    void enqueueTask(const std::function<void()>& task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.push(task);
            if (workers.size() < maxThreads && tasks.size() > workers.size()) {
                workers.emplace_back(&DynamicThreadPool::worker, this);
            }
        }
        condition.notify_one();
    }

private:
    void worker() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) {
                    return;
                }
                task = std::move(tasks.front());
                tasks.pop();
            }
            task();
        }
    }

    size_t minThreads;
    size_t maxThreads;
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

void dynamicTask(int id) {
    std::cout << "Dynamic Task " << id << " is being processed by thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main() {
    DynamicThreadPool dynamicPool(2, 6);

    for (int i = 1; i <= 20; ++i) {
        dynamicPool.enqueueTask([i] { dynamicTask(i); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}

