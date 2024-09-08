#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <vector>


class MonitorBuffer {
public:
    MonitorBuffer(size_t size) : size(size), count(0), front(0), rear(0), buffer(size) {}

    void produce(int item) {
        std::unique_lock<std::mutex> lock(mutex);
        condVarNotFull.wait(lock, [this] { return count < size; });

        buffer[rear] = item;
        rear = (rear + 1) % size;
        ++count;
        std::cout << "Produced " << item << " by thread " << std::this_thread::get_id() << std::endl;

        condVarNotEmpty.notify_all();
    }

    int consume() {
        std::unique_lock<std::mutex> lock(mutex);
        condVarNotEmpty.wait(lock, [this] { return count > 0; });

        int item = buffer[front];
        front = (front + 1) % size;
        --count;
        std::cout << "Consumed " << item << " by thread " << std::this_thread::get_id() << std::endl;

        condVarNotFull.notify_all();
        return item;
    }

private:
    size_t size;
    size_t count;
    size_t front;
    size_t rear;
    std::vector<int> buffer;
    std::mutex mutex;
    std::condition_variable condVarNotFull;
    std::condition_variable condVarNotEmpty;
};

void producerTask(MonitorBuffer& buffer, int items) {
    for (int i = 0; i < items; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        buffer.produce(i);
    }
}

void consumerTask(MonitorBuffer& buffer, int items) {
    for (int i = 0; i < items; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        buffer.consume();
    }
}

int main() {
    MonitorBuffer buffer(10);

    std::thread producer1(producerTask, std::ref(buffer), 20);
    std::thread producer2(producerTask, std::ref(buffer), 20);
    std::thread consumer1(consumerTask, std::ref(buffer), 20);
    std::thread consumer2(consumerTask, std::ref(buffer), 20);

    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    return 0;
}