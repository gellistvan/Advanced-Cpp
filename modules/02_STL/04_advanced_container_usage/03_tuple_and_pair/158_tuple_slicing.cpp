#include <iostream>
#include <tuple>

template <std::size_t... Is, typename Tuple>
auto slice(Tuple&& t, std::index_sequence<Is...>) {
    return std::make_tuple(std::get<Is>(std::forward<Tuple>(t))...);
}

template <std::size_t Start, std::size_t End, typename Tuple>
auto slice(Tuple&& t) {
    return slice(t, std::make_index_sequence<End - Start>{});
}

int main() {
    std::tuple<int, double, std::string, char> t = std::make_tuple(1, 3.14, "hello", 'A');

    auto t_slice = slice<1, 3>(t);

    std::cout << "Sliced tuple: ("
              << std::get<0>(t_slice) << ", "
              << std::get<1>(t_slice) << ")" << std::endl;

    return 0;
}