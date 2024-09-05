#include <iostream>
// corrected from the book

// Compile-time representation of an empty map
struct EmptyMap {};

// Key-value pair template
template<int Key, int Value>
struct Pair {
    static constexpr int key = Key;
    static constexpr int value = Value;
};

// Map template
template<typename... Pairs>
struct Map {};

// Function to get a value from the map by key
template<int Key, typename Map>
struct Get;

template<int Key>
struct Get<Key, EmptyMap> {
    static constexpr int value = -1; // Indicate key not found
};

template<int Key>
struct Get<Key, Map<>> {
    static constexpr int value = -1; // Indicate key not found when the map is empty
};

template<int Key, int Value, typename... Rest>
struct Get<Key, Map<Pair<Key, Value>, Rest...>> {
    static constexpr int value = Value;
};

template<int Key, int OtherKey, int OtherValue, typename... Rest>
struct Get<Key, Map<Pair<OtherKey, OtherValue>, Rest...>> {
    static constexpr int value = Get<Key, Map<Rest...>>::value;
};

int main() {
    using MyMap = Map<Pair<1, 100>, Pair<2, 200>, Pair<3, 300>>;
    constexpr int value1 = Get<1, MyMap>::value; // 100
    constexpr int value2 = Get<2, MyMap>::value; // 200
    constexpr int value3 = Get<4, MyMap>::value; // -1 (not found)

    std::cout << "Value for key 1: " << value1 << std::endl;
    std::cout << "Value for key 2: " << value2 << std::endl;
    std::cout << "Value for key 3: " << value3 << std::endl; // Output: -1

    return 0;
}
