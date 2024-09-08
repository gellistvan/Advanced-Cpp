#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

class MonitorObject {
public:
    MonitorObject() : value(0) {}

    void increment() {
        std::unique_lock<std::mutex> lock(mutex);
        ++value;
        std::cout << "Value incremented to " << value << " by thread " << std::this_thread::get_id() << std::endl;
        condVar.notify_all();
    }

    void waitForValue(int target) {
        std::unique_lock<std::mutex> lock(mutex);
        condVar.wait(lock, [this, target] { return value >= target; });
        std::cout << "Target value " << target << " reached by thread " << std::this_thread::get_id() << std::endl;
    }

    int getValue() const {
        std::unique_lock<std::mutex> lock(mutex);
        return value;
    }

private:
    mutable std::mutex mutex;
    std::condition_variable condVar;
    int value;
};

void incrementTask(MonitorObject& monitor) {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        monitor.increment();
    }
}

void waitTask(MonitorObject& monitor, int target) {
    monitor.waitForValue(target);
}

int main() {
    MonitorObject monitor;

    std::thread t1(incrementTask, std::ref(monitor));
    std::thread t2(waitTask, std::ref(monitor), 3);
    std::thread t3(waitTask, std::ref(monitor), 5);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}