#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>  // for std::accumulate
#include <stdexcept> // for exception handling
// corrected from the book


template <typename T>
class ExtendedVector : public std::vector<T> {
public:
    using std::vector<T>::vector; // Inherit constructors from std::vector

    // Print all elements in the vector
    void print() const {
        for (const auto& elem : *this) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    // Get the sum of all elements (works if T supports + operator)
    T sum() const {
        return std::accumulate(this->begin(), this->end(), T{});
    }

    // Get the average of all elements
    T average() const {
        if (this->empty()) {
            throw std::runtime_error("Vector is empty, cannot calculate average");
        }
        return sum() / static_cast<T>(this->size());
    }

    // Get the maximum element (works if T supports comparison operators)
    T max() const {
        if (this->empty()) {
            throw std::runtime_error("Vector is empty, no maximum element");
        }
        return *std::max_element(this->begin(), this->end());
    }

    // Get the minimum element
    T min() const {
        if (this->empty()) {
            throw std::runtime_error("Vector is empty, no minimum element");
        }
        return *std::min_element(this->begin(), this->end());
    }

    // Find an element in the vector
    bool contains(const T& value) const {
        return std::find(this->begin(), this->end(), value) != this->end();
    }

    // Remove all occurrences of a specific element
    void remove(const T& value) {
        this->erase(std::remove(this->begin(), this->end(), value), this->end());
    }

    // Sort the vector in ascending order
    void sortAscending() {
        std::sort(this->begin(), this->end());
    }

    // Sort the vector in descending order
    void sortDescending() {
        std::sort(this->begin(), this->end(), std::greater<T>());
    }
};

int main() {
    ExtendedVector<int> ev = {5, 2, 8, 1, 9, 4};

    // Print initial vector
    std::cout << "Initial Vector: ";
    ev.print();

    // Print sum of elements
    std::cout << "Sum: " << ev.sum() << std::endl;

    // Print average of elements
    std::cout << "Average: " << ev.average() << std::endl;

    // Print maximum and minimum elements
    std::cout << "Max: " << ev.max() << std::endl;
    std::cout << "Min: " << ev.min() << std::endl;

    // Check if vector contains the value 8
    if (ev.contains(8)) {
        std::cout << "Vector contains 8." << std::endl;
    } else {
        std::cout << "Vector does not contain 8." << std::endl;
    }

    // Remove the value 8
    ev.remove(8);
    std::cout << "Vector after removing 8: ";
    ev.print();

    // Sort in ascending order
    ev.sortAscending();
    std::cout << "Vector after sorting in ascending order: ";
    ev.print();

    // Sort in descending order
    ev.sortDescending();
    std::cout << "Vector after sorting in descending order: ";
    ev.print();

    return 0;
}
