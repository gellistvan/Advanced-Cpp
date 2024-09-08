#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

// Box manipulator from the previous example
class Box {
public:
    explicit Box(const std::string& content) : content_(content) {}

    friend std::ostream& operator<<(std::ostream& os, const Box& box) {
        int width = static_cast<int>(box.content_.size()) + 4;
        os << "+" << std::string(width - 2, '-') << "+" << std::endl;
        os << "| " << box.content_ << " |" << std::endl;
        os << "+" << std::string(width - 2, '-') << "+" << std::endl;
        return os;
    }

private:
    std::string content_;
};

// Color manipulator from the previous example
enum class Color {
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    RESET = 0
};

class ColorManipulator {
public:
    explicit ColorManipulator(Color color) : color_(color) {}

    friend std::ostream& operator<<(std::ostream& os, const ColorManipulator& manip) {
        return os << "\033[" << static_cast<int>(manip.color_) << "m";
    }

private:
    Color color_;
};

// Factory functions
Box box(const std::string& content) {
    return Box(content);
}

ColorManipulator set_color(Color color) {
    return ColorManipulator(color);
}

// Combined usage
int main() {
    std::cout << set_color(Color::MAGENTA) << box("Exciting Colored Box!") << set_color(Color::RESET);
    std::cout << set_color(Color::CYAN) << box("Color and Box Together!") << set_color(Color::RESET);
}
