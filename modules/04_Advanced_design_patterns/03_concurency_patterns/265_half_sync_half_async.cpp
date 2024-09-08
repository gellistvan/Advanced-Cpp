#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>
#include <chrono>

class AsyncLayer {
public:
    AsyncLayer() : stop(false) {
        asyncThread = std::thread(&AsyncLayer::run, this);
    }

    ~AsyncLayer() {
        stop = true;
        if (asyncThread.joinable()) {
            asyncThread.join();
        }
    }

    void postTask(const std::function<void()>& task) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            taskQueue.push(task);
        }
        queueCondVar.notify_one();
    }

private:
    void run() {
        while (!stop) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                queueCondVar.wait(lock, [this] { return !taskQueue.empty() || stop; });
                if (stop && taskQueue.empty()) {
                    return;
                }
                task = taskQueue.front();
                taskQueue.pop();
            }
            task();
        }
    }

    std::thread asyncThread;
    std::mutex queueMutex;
    std::condition_variable queueCondVar;
    std::queue<std::function<void()>> taskQueue;
    std::atomic<bool> stop;
};

class QueueingLayer {
public:
    void addRequest(const std::function<void()>& request) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            requestQueue.push(request);
        }
        queueCondVar.notify_one();
    }

    std::function<void()> getRequest() {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCondVar.wait(lock, [this] { return !requestQueue.empty(); });
        auto request = requestQueue.front();
        requestQueue.pop();
        return request;
    }

private:
    std::mutex queueMutex;
    std::condition_variable queueCondVar;
    std::queue<std::function<void()>> requestQueue;
};


class SyncLayer {
public:
    SyncLayer(QueueingLayer& queueLayer, int numThreads) : queueLayer(queueLayer), stop(false) {
        for (int i = 0; i < numThreads; ++i) {
            workerThreads.emplace_back(&SyncLayer::processRequests, this);
        }
    }

    ~SyncLayer() {
        stop = true;
        for (auto& thread : workerThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

private:
    void processRequests() {
        while (!stop) {
            auto request = queueLayer.getRequest();
            request();
        }
    }

    QueueingLayer& queueLayer;
    std::vector<std::thread> workerThreads;
    std::atomic<bool> stop;
};

void asyncOperation(QueueingLayer& queueLayer) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    queueLayer.addRequest([]() {
        std::cout << "Processing request by thread " << std::this_thread::get_id() << std::endl;
    });
}

int main() {
    QueueingLayer queueLayer;
    AsyncLayer asyncLayer;
    SyncLayer syncLayer(queueLayer, 4);

    for (int i = 0; i < 10; ++i) {
        asyncLayer.postTask([&queueLayer]() { asyncOperation(queueLayer); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}

