#include <iostream>
#include <vector>
#include <ranges>
#include <concepts>
// corrected from the book


// Define a concept to check if a type is a range of integral elements
template<typename R>
concept IntegralRange = std::ranges::range<R> && std::integral<std::ranges::range_value_t<R>>;

// Function to print the elements of a range that satisfies the IntegralRange concept
void print_integral_range(IntegralRange auto&& range) {
    for (auto&& value : range) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    print_integral_range(vec); // Output: 1 2 3 4 5

    std::vector<std::string> str_vec = {"Hello", "World"};
    //

    // Error: no matching function to call 'print_integral_range'
    // print_integral_range(str_vec);

    return 0;
}