#include <numeric>
#include <array>
#include <algorithm>
#include <iostream>
// corrected from the book


template <typename T>
class Buffer {
public:
    constexpr Buffer(size_t n) noexcept : size_(n), mem_(new T[n]) { }
    constexpr ~Buffer() noexcept { delete [] mem_; }

    // Copy constructor
    constexpr Buffer(const Buffer& other) noexcept : size_(other.size_) {
        mem_ = new T[size_];
        std::copy(other.mem_, other.mem_ + size_, mem_);
    }

    // Move constructor
    constexpr Buffer(Buffer&& other) noexcept
        : mem_(other.mem_), size_(other.size_) {
        other.mem_ = nullptr;
        other.size_ = 0;
    }

    // Copy assignment
    constexpr Buffer& operator=(const Buffer& other) noexcept {
        if (this != &other) {
            delete[] mem_;
            size_ = other.size_;
            mem_ = new T[size_];
            std::copy(other.mem_, other.mem_ + size_, mem_);
        }
        return *this;
    }

    // Move assignment
    constexpr Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] mem_;
            mem_ = other.mem_;
            size_ = other.size_;
            other.mem_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    constexpr T& operator[](size_t id) noexcept { return mem_[id]; }
    constexpr const T& operator[](size_t id) const noexcept{ return mem_[id]; }

    constexpr T* data() const noexcept { return mem_; }
    constexpr size_t size() const noexcept { return size_; }

private:
    T *mem_ { nullptr };
    size_t size_ { 0 };
};

constexpr int naiveSumBuffer(unsigned int n) {
    Buffer<int> buf(n); // almost a vector class!
    std::iota(buf.data(), buf.data()+n, 1);
    return std::accumulate(buf.data(), buf.data()+n, 0);
}

template <size_t N, typename T>
constexpr auto prepareLookup() {
    Buffer<T> buf(N);
    std::array<T, N> out;
    std::copy(buf.data(), buf.data()+N, out.begin());
    return out;
}

int main() {
    // Test naiveSumBuffer
    int sum = naiveSumBuffer(15);
    std::cout << "Sum: " << sum << std::endl;

    // Test buffer with custom size
    Buffer<int> buf(10);
    std::iota(buf.data(), buf.data() + buf.size(), 1);
    int totalSum = std::accumulate(buf.data(), buf.data() + buf.size(), 0);
    std::cout << "Total Sum: " << totalSum << std::endl;

    return 0;
}