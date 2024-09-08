#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::vector<int> vec;

    std::cout << "Enter integers (end with Ctrl+D or Ctrl+Z): ";
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(vec));

    std::cout << "Square roots: ";
    std::transform(vec.begin(), vec.end(),
                   std::ostream_iterator<double>(std::cout, " "),
                   [](int n) { return std::sqrt(n); });
    std::cout << std::endl;

    return 0;
}