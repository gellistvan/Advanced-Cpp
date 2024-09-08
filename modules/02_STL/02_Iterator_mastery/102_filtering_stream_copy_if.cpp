#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

bool is_even(int n) {
    return n % 2 == 0;
}

int main() {
    std::vector<int> vec;

    std::cout << "Enter integers (end with Ctrl+D or Ctrl+Z): ";
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(vec));

    std::cout << "Even numbers: ";
    std::copy_if(vec.begin(), vec.end(),
                 std::ostream_iterator<int>(std::cout, " "),
                 is_even);
    std::cout << std::endl;

    return 0;
}