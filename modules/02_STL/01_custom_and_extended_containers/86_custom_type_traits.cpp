#include <type_traits>
#include <iostream>
#include <string>
#include <vector>

// Example custom class to test the container with class types
class CustomClass {
public:
    void display() const {
        std::cout << "CustomClass instance displaying..." << std::endl;
    }
};

// Primary template for a custom container
template <typename T, typename Enable = void>
class CustomContainer;

// Specialization for integral types
template <typename T>
class CustomContainer<T, typename std::enable_if<std::is_integral_v<T>>::type> {
public:
    void process(const T& value) {
        std::cout << "Processing integral value: " << value << std::endl;
    }

    // Additional operation for integral types
    T bitwiseInvert(const T& value) {
        return ~value;
    }
};

// Specialization for floating-point types
template <typename T>
class CustomContainer<T, typename std::enable_if<std::is_floating_point_v<T>>::type> {
public:
    void process(const T& value) {
        std::cout << "Processing floating-point value: " << value << std::endl;
    }

    // Additional operation for floating-point types
    T addPrecision(const T& value) {
        return value + static_cast<T>(0.0001); // Simulates adding precision
    }
};

// Specialization for std::basic_string (string type)
template <typename T>
class CustomContainer<T, typename std::enable_if<std::is_same_v<T, std::basic_string<typename T::value_type>>>::type> {
public:
    void process(const T& value) {
        std::cout << "Processing string: " << value << std::endl;
    }

    // Additional operation for string types
    T toUpperCase(const T& value) {
        std::string upper;
        for (char c : value) {
            upper += std::toupper(c);
        }
        return upper;
    }
};


int main() {
    // Integral type
    CustomContainer<int> intContainer;
    intContainer.process(42);
    std::cout << "Bitwise inverted value: " << intContainer.bitwiseInvert(42) << std::endl;

    // Floating-point type
    CustomContainer<double> doubleContainer;
    doubleContainer.process(3.14);
    std::cout << "Value with added precision: " << doubleContainer.addPrecision(3.14) << std::endl;

    // String type
    CustomContainer<std::string> stringContainer;
    stringContainer.process("Hello World");
    std::cout << "Uppercase string: " << stringContainer.toUpperCase("Hello World") << std::endl;

    // This will result in a compile-time error because the type is not supported
    CustomClass myClass;
    // CustomContainer<CustomClass> customClassContainer;
    // customClassContainer.process(myClass);

    return 0;
}
