#include <iostream>
#include <deque>

class CircularBuffer {
public:
    CircularBuffer(size_t size) : max_size(size) {}

    void add(int value) {
        if (buffer.size() == max_size) {
            buffer.pop_front();
        }
        buffer.push_back(value);
    }

    void print() const {
        for (const auto& elem : buffer) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

private:
    std::deque<int> buffer;
    size_t max_size;
};

int main() {
    CircularBuffer cb(3);

    cb.add(1);
    cb.add(2);
    cb.add(3);
    cb.print();

    cb.add(4);
    cb.print();

    cb.add(5);
    cb.print();

    return 0;
}