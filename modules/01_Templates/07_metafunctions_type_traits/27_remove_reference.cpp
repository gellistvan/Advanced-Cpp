#include <vector>

int main() {
    std::vector<int, SimpleAllocator<int>> vec;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    for (const auto& val : vec) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    return 0;
}