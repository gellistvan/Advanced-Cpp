#include <iostream>
#include <type_traits>

// Metafunction to remove const qualifier
template<typename T>
struct RemoveConst {
    using type = T;
};

template<typename T>
struct RemoveConst<const T> {
    using type = T;
};

// Metafunction class to add a pointer to a type
struct AddPointer {
    template<typename T>
    struct apply {
        using type = T*;
    };
};

// Metafunction class to remove pointer if present
struct RemovePointer {
    template<typename T>
    struct apply {
        using type = T;
    };

    template<typename T>
    struct apply<T*> {
        using type = T;
    };
};

int main() {
    std::cout << std::is_same<int, RemoveConst<const int>::type>::value << std::endl; // Output: 1 (true)
    std::cout << std::is_same<int, RemoveConst<int>::type>::value << std::endl;       // Output: 1 (true)

    using T = AddPointer::apply<int>::type;
    std::cout << std::is_same<int*, T>::value << std::endl; // Output: 1 (true)

    using T1 = RemovePointer::apply<int>::type;
    using T2 = RemovePointer::apply<int*>::type;

    std::cout << std::is_same<int, T1>::value << std::endl;   // Output: 1 (true)
    std::cout << std::is_same<int, T2>::value << std::endl;   // Output: 1 (true)
    std::cout << std::is_same<int*, T1>::value << std::endl;  // Output: 0 (false)
    std::cout << std::is_same<int*, T2>::value << std::endl;  // Output: 0 (false)
    return 0;
}