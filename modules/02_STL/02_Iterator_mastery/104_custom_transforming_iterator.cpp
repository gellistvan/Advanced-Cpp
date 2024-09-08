#include <iostream>
#include <iterator>
#include <functional>
#include <vector>
#include <algorithm>

// Manually define iterator traits
template <typename T, typename Func>
class TransformingIStreamIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::input_iterator_tag;

    TransformingIStreamIterator(std::istream& is, Func func, T quit_val = -1)
        : stream(&is), transform_func(func), quit_value(quit_val), value(), end_of_stream(false) {
        ++(*this); // Pre-load the first value
    }

    // End-of-stream constructor
    TransformingIStreamIterator()
        : stream(nullptr), transform_func(nullptr), quit_value(-1), end_of_stream(true) {}

    T operator*() const { return value; }

    TransformingIStreamIterator& operator++() {
        if (stream && *stream >> value) {
            if (value == quit_value) {  // Check for the sentinel value (e.g., -1)
                end_of_stream = true;    // Mark as end of stream
            } else {
                value = transform_func(value);  // Apply the transformation
            }
        } else {
            end_of_stream = true;  // Mark the end of the stream when there's no more input
        }
        return *this;
    }

    TransformingIStreamIterator operator++(int) {
        TransformingIStreamIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const TransformingIStreamIterator& other) const {
        return end_of_stream == other.end_of_stream;
    }

    bool operator!=(const TransformingIStreamIterator& other) const {
        return !(*this == other);
    }

private:
    std::istream* stream;
    Func transform_func;
    T quit_value;      // Sentinel value to exit the loop
    T value;
    bool end_of_stream;
};

int main() {
    std::function<int(int)> transform_func = [](int n) { return n * n; };
    int quit_val = -1;  // Sentinel value to quit

    // Initialize iterators with the quit value
    TransformingIStreamIterator<int, std::function<int(int)>> begin(std::cin, transform_func, quit_val);
    TransformingIStreamIterator<int, std::function<int(int)>> end;

    std::vector<int> vec;
    std::copy(begin, end, std::back_inserter(vec));

    std::cout << "Transformed input: ";
    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}
