#include <iostream>
#include <utility>
#include <type_traits>
#include <vector>

// Helper to determine the index of a type in a list of types
template <typename T, typename... Types>
struct IndexOf;

template <typename T, typename First, typename... Rest>
struct IndexOf<T, First, Rest...> {
    static constexpr size_t value = std::is_same<T, First>::value ? 0 : 1 + IndexOf<T, Rest...>::value;
};

template <typename T>
struct IndexOf<T> {
    static constexpr size_t value = 0;
};

// Custom Variant class
template <typename... Types>
class Variant {
    static constexpr size_t data_size = std::max({sizeof(Types)...});
    static constexpr size_t data_align = std::max({alignof(Types)...});

    using Storage = typename std::aligned_storage<data_size, data_align>::type;

    Storage data;
    size_t active_index;

public:
    // Constructor for the first type in Types...
    template <typename T>
    Variant(T&& value) {
        static_assert(is_valid_type<T>(), "Invalid type for Variant");
        construct(std::forward<T>(value));
    }

    // Destructor to call the active type's destructor
    ~Variant() {
        destroy();
    }

    // Copy constructor
    Variant(const Variant& other) : active_index(other.active_index) {
        visit([this](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            new (&data) T(val);
        }, other);
    }

    // Assignment operator
    Variant& operator=(const Variant& other) {
        if (this != &other) {
            destroy();
            active_index = other.active_index;
            visit([this](const auto& val) {
                using T = std::decay_t<decltype(val)>;
                new (&data) T(val);
            }, other);
        }
        return *this;
    }

    // Retrieve the value as a specific type
    template <typename T>
    T& get() {
        static_assert(is_valid_type<T>(), "Invalid type for Variant");
        if (active_index != IndexOf<T, Types...>::value) {
            throw std::bad_variant_access();
        }
        return *reinterpret_cast<T*>(&data);
    }

    // Retrieve the value as a specific type (const version)
    template <typename T>
    const T& get() const {
        static_assert(is_valid_type<T>(), "Invalid type for Variant");
        if (active_index != IndexOf<T, Types...>::value) {
            throw std::bad_variant_access();
        }
        return *reinterpret_cast<const T*>(&data);
    }

    // Get the index of the currently active type
    size_t index() const {
        return active_index;
    }

    // Visit function: apply a visitor to the active type
    template <typename Visitor>
    void visit(Visitor&& visitor) {
        visit_impl(std::forward<Visitor>(visitor), std::make_index_sequence<sizeof...(Types)>{});
    }

    template <typename Visitor>
    void visit(Visitor&& visitor) const {
        visit_impl(std::forward<Visitor>(visitor), std::make_index_sequence<sizeof...(Types)>{});
    }

private:
    // Helper to check if a type is in the Types...
    template <typename T>
    static constexpr bool is_valid_type() {
        return (std::is_same_v<T, Types> || ...);
    }

    // Helper to construct an object of type T in the storage
    template <typename T>
    void construct(T&& value) {
        active_index = IndexOf<T, Types...>::value;
        new (&data) T(std::forward<T>(value));
    }

    // Helper to destroy the active object
    void destroy() {
        visit([](auto& val) {
            using T = std::decay_t<decltype(val)>;
            val.~T();
        });
    }

    // Compile-time visitor implementation
    template <typename Visitor, size_t... Indices>
    void visit_impl(Visitor&& visitor, std::index_sequence<Indices...>) {
        (void)((active_index == Indices && (visitor(get_by_index<Indices>()), true)) || ...);
    }

    template <typename Visitor, size_t... Indices>
    void visit_impl(Visitor&& visitor, std::index_sequence<Indices...>) const {
        (void)((active_index == Indices && (visitor(get_by_index<Indices>()), true)) || ...);
    }

    // Helper to retrieve the value by its index
    template <size_t Index>
    auto& get_by_index() {
        using T = std::tuple_element_t<Index, std::tuple<Types...>>;
        return *reinterpret_cast<T*>(&data);
    }

    // Const version of the helper to retrieve the value by its index
    template <size_t Index>
    const auto& get_by_index() const {
        using T = std::tuple_element_t<Index, std::tuple<Types...>>;
        return *reinterpret_cast<const T*>(&data);
    }
};

// Shape types for demonstration
struct Sphere {
    void draw() const {
        std::cout << "draw sphere\n";
    }
};

struct Square {
    void draw() const {
        std::cout << "draw square\n";
    }
};

struct Triangle {
    void draw() const {
        std::cout << "draw triangle\n";
    }
};

// Test function for the compile-time variant with visit
int main() {
    std::vector<Variant<Sphere, Square, Triangle>> shapes {Sphere{}, Square{}, Triangle{}};


    for (const auto& s : shapes)
    {
        s.visit([](const auto& s) { s.draw(); });
    }

    return 0;
}
