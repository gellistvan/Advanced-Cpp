#include <iostream>
#include <tuple>

template <typename... Args>
void print_tuple(const std::tuple<Args...>& t) {
    std::apply([](const Args&... args) {
        ((std::cout << args << ' '), ...);
    }, t);
    std::cout << std::endl;
}

int main() {
    std::tuple<int, double, std::string> t = std::make_tuple(1, 3.14, "hello");
    print_tuple(t);

    return 0;
}