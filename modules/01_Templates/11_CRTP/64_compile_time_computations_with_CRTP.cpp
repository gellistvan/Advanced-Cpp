#include <iostream>
#include <array>

template <typename Derived>
class ArrayWrapper {
public:
    void print() const {
        static_cast<const Derived*>(this)->print();
    }
};

template <typename T, size_t N>
class StaticArray : public ArrayWrapper<StaticArray<T, N>> {
public:
    StaticArray() : data{} {}

    void print() const {
        for (const auto& elem : data) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    T& operator[](size_t index) {
        return data[index];
    }

private:
    std::array<T, N> data;
};

int main() {
    StaticArray<int, 5> arr;
    for (size_t i = 0; i < 5; ++i) {
        arr[i] = static_cast<int>(i * i);
    }
    arr.print(); // Output: 0 1 4 9 16

    return 0;
}