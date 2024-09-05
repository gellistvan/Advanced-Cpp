#include <iostream>
#include <vector>
#include <algorithm>

// Policy class for ascending order
class Ascending {
public:
    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

// Policy class for descending order
class Descending {
public:
    template <typename T>
    bool operator()(const T& a,

 const T& b) const {
        return a > b;
    }
};

template <typename Derived, typename Policy>
class Sorter {
public:
    void sort(std::vector<int>& data) const {
        std::sort(data.begin(), data.end(), Policy());
        static_cast<const Derived*>(this)->print(data);
    }
};

class AscendingSorter : public Sorter<AscendingSorter, Ascending> {
public:
    void print(const std::vector<int>& data) const {
        std::cout << "Ascending: ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

class DescendingSorter : public Sorter<DescendingSorter, Descending> {
public:
    void print(const std::vector<int>& data) const {
        std::cout << "Descending: ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<int> data = {5, 2, 9, 1, 5, 6};

    AscendingSorter ascSorter;
    DescendingSorter descSorter;

    ascSorter.sort(data); // Output: Ascending: 1 2 5 5 6 9
    descSorter.sort(data); // Output: Descending: 9 6 5 5 2 1

    return 0;
}