#include <iostream>
#include <typeinfo>
// corrected from the book

// General template for custom allocator
template<typename T>
class CustomAllocator {
public:
    T* allocate(size_t n) {
        std::cout << "Allocating " << n << " objects of type " << typeid(T).name() << std::endl;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, size_t n) {
        std::cout << "Deallocating " << n << " objects of type " << typeid(T).name() << std::endl;
        ::operator delete(p);
    }
};

// Specialization for pointer types
template<typename T>
class CustomAllocator<T*> {
public:
    T** allocate(size_t n) {
        std::cout << "Allocating " << n << " pointers to type " << typeid(T).name() << std::endl;
        return static_cast<T**>(::operator new(n * sizeof(T*)));
    }

    void deallocate(T** p, size_t n) {
        std::cout << "Deallocating " << n << " pointers to type " << typeid(T).name() << std::endl;
        ::operator delete(p);
    }
};

int main() {
    CustomAllocator<int> intAllocator;
    int* intArray = intAllocator.allocate(5);
    intAllocator.deallocate(intArray, 5);

    CustomAllocator<int*> ptrAllocator;
    int** ptrArray = ptrAllocator.allocate(5);
    ptrAllocator.deallocate(ptrArray, 5);

    return 0;
}
