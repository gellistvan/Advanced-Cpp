#include <variant>
#include <iostream>
#include <string>
#include <vector>

struct MouseEvent {
    int x, y;
};

struct KeyEvent {
    int keycode;
};

using Event = std::variant<MouseEvent, KeyEvent>;

void handleEvent(const Event& event) {
    std::visit([](auto&& e) {
        using T = std::decay_t<decltype(e)>;
        if constexpr (std::is_same_v<T, MouseEvent>) {
            std::cout << "MouseEvent at (" << e.x << ", " << e.y << ")" << std::endl;
        } else if constexpr (std::is_same_v<T, KeyEvent>) {
            std::cout << "KeyEvent with keycode " << e.keycode << std::endl;
        }
    }, event);
}

int main() {
    std::vector<Event> events = {
        MouseEvent{100, 200},
        KeyEvent{42},
        MouseEvent{150, 250},
    };

    for (const auto& event : events) {
        handleEvent(event);
    }

    // Output:
    // MouseEvent at (100, 200)
    // KeyEvent with keycode 42
    // MouseEvent at (150, 250)

    return 0;
}