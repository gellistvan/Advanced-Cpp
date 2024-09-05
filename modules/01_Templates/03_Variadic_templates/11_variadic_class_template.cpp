#include <iostream>

// Base case: empty tuple
template<typename... Args>
class Tuple {};

// Recursive case: tuple with at least one element
template<typename Head, typename... Tail>
class Tuple<Head, Tail...> {
public:
    Head head;
    Tuple<Tail...> tail;

    Tuple(Head h, Tail... t) : head(h), tail(t...) {}

    void print() const {
        std::cout << head << std::endl;
        tail.print();
    }
};

// Specialization for empty tuple
template<>
class Tuple<> {
public:
    void print() const {}
};

int main() {
    Tuple<int, double, const char*, char> t(1, 2.5, "Hello", 'A');
    t.print();
    // Output:
    // 1
    // 2.5
    // Hello
    // A
    return 0;
}
