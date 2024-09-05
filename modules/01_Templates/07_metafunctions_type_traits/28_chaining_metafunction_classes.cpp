#include <iostream>
#include <type_traits>

// Metafunction class to add a pointer to a type
struct AddPointer {
    template<typename T>
    struct apply {
        using type = T*;
    };
};

// Metafunction class to remove const qualifier
struct RemoveConst {
    template<typename T>
    struct apply {
        using type = T;
    };

    template<typename T>
    struct apply<const T> {
        using type = T;
    };
};

// Metafunction class to chain multiple metafunctions
template<typename F1, typename F2>
struct Compose {
    template<typename T>
    struct apply {
        using type = typename F1::template apply<typename F2::template apply<T>::type>::type;
    };
};

int main() {
    using T = Compose<AddPointer, RemoveConst>::apply<const int>::type;
    std::cout << std::is_same<int*, T>::value << std::endl; // Output: 1 (true)
    return 0;
}