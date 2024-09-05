#include <iostream>
#include <vector>
#include <ranges>

// Function to filter and transform data using ranges
void filter_and_transform(std::vector<int>& data) {
    auto view = data
        | std::ranges::views::filter([](int n) { return n % 2 == 0; })
        | std::ranges::views::transform([](int n) { return n * 10; });

    // Print the elements of the view
    for (int value : view) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    filter_and_transform(data); // Output: 20 40 60 80 100
    return 0;
}