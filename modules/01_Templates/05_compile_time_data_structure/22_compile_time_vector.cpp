#include <iostream>
#include <array>

// Compile-time vector class
template<typename T, std::size_t N>
class Vector {
public:
    constexpr Vector() : data{} {}

    constexpr T& operator[](std::size_t index) {
        return data[index];
    }

    constexpr const T& operator[](std::size_t index) const {
        return data[index];
    }

    constexpr std::size_t size() const {
        return N;
    }

private:
    std::array<T, N> data;
};

int main() {
    constexpr Vector<int, 5> vec;
    static_assert(vec.size() == 5, "Size check failed");
    
    // Print elements of the compile-time vector
    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " "; // Default-initialized to zero
    }
    std::cout << std::endl;

    return 0;
}