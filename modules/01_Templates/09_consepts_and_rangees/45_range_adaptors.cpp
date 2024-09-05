#include <iostream>
#include <vector>
#include <ranges>

// Function to demonstrate range adaptors
int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Create a view that filters out even numbers and multiplies the remaining numbers by 2
    auto view = vec
        | std::ranges::views::filter([](int n) { return n % 2 != 0; })
        | std::ranges::views::transform([](int n) { return n * 2; });

    // Print the elements of the view
    for (int i : view) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // Output: 2 6 10 14 18

    return 0;
}