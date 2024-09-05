#include <iostream>
#include <vector>
#include <ranges>

// Basic usage of ranges
int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Use ranges to create a view of the elements
    auto view = vec | std::ranges::views::reverse;

    // Print the elements of the view
    for (int i : view) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // Output: 5 4 3 2 1

    return 0;
}