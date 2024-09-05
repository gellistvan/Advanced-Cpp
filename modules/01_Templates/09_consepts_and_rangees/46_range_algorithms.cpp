#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

// Function to demonstrate range algorithms
int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // Create a view that takes the first 3 elements and then sorts them in descending order
    auto view = vec
        | std::ranges::views::take(3)
        | std::ranges::views::transform([](int n) { return n + 1; });

    // Print the elements of the view
    for (int i : view) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // Output: 11 21 31

    // Sort the original vector using range algorithms
    std::ranges::sort(vec);

    // Print the sorted vector
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // Output: 10 20 30 40 50

    return 0;
}