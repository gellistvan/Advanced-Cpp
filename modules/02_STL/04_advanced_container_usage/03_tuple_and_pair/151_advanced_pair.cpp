#include <iostream>
#include <map>

int main() {
    std::map<std::pair<int, int>, std::string> coord_map;
    coord_map[std::make_pair(1, 2)] = "Point A";
    coord_map[std::make_pair(2, 3)] = "Point B";

    for (const auto& item : coord_map) {
        std::cout << "Coordinates: (" << item.first.first << ", " << item.first.second << ") -> " << item.second << std::endl;
    }

    return 0;
}