#include <iostream>

// General template for storing a value
template<typename T>
class Storage {
public:
    explicit Storage(T value) : value(value) {}

    void print() const {
        std::cout << "Value: " << value << std::endl;
    }

private:
    T value;
};

// Partial specialization for pointers
template<typename T>
class Storage<T*> {
public:
    explicit Storage(T* value) : value(value) {}

    void print() const {
        if (value) {
            std::cout << "Pointer value: " << *value << std::endl;
        } else {
            std::cout << "Null pointer" << std::endl;
        }
    }

private:
    T* value;
};

int main() {
    Storage<int> s1(42);
    s1.print(); // Output: Value: 42

    int x = 100;
    Storage<int*> s2(&x);
    s2.print(); // Output: Pointer value: 100

    Storage<int*> s3(nullptr);
    s3.print(); // Output: Null pointer

    return 0;
}