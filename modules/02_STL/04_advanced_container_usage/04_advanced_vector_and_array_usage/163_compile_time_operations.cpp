#include <iostream>
#include <array>

constexpr int array_sum(const std::array<int, 5>& arr) {
    int sum = 0;
    for (const auto& elem : arr) {
        sum += elem;
    }
    return sum;
}

int main() {
    constexpr std::array<int, 5> arr = {1, 2, 3, 4, 5};
    constexpr int sum = array_sum(arr);

    std::cout << "Sum of array elements: " << sum << std::endl;

    return 0;
}