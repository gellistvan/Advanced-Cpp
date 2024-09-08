#include <iostream>
#include <stdexcept>

template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(std::size_t capacity)
        : data(new T[capacity]), capacity(capacity), size(0), front(0), back(0) {}

    ~RingBuffer() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            throw std::overflow_error("Ring buffer overflow");
        }
        data[back] = value;
        back = (back + 1) % capacity;
        ++size;
    }

    void pop_front() {
        if (size == 0) {
            throw std::underflow_error("Ring buffer underflow");
        }
        front = (front + 1) % capacity;
        --size;
    }

    const T& front_value() const {
        if (size == 0) {
            throw std::underflow_error("Ring buffer is empty");
        }
        return data[front];
    }

    bool empty() const {
        return size == 0;
    }

    bool full() const {
        return size == capacity;
    }

    std::size_t get_size() const {
        return size;
    }

    void print() const {
        for (std::size_t i = 0; i < size; ++i) {
            std::cout << data[(front + i) % capacity] << ' ';
        }
        std::cout << std::endl;
    }

private:
    T* data;
    std::size_t capacity;
    std::size_t size;
    std::size_t front;
    std::size_t back;
};

int main() {
    RingBuffer<int> rb(5);

    rb.push_back(1);
    rb.push_back(2);
    rb.push_back(3);
    rb.push_back(4);
    rb.push_back(5);

    rb.print();

    rb.pop_front();
    rb.pop_front();

    rb.print();

    rb.push_back(6);
    rb.push_back(7);

    rb.print();

    return 0;
}