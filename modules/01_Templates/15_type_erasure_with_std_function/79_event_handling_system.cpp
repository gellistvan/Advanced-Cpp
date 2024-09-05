#include <functional>
#include <iostream>
#include <vector>

class Button {
public:
    using ClickHandler = std::function<void()>;

    void setClickHandler(ClickHandler handler) {
        clickHandler = std::move(handler);
    }

    void click() const {
        if (clickHandler) {
            clickHandler();
        }
    }

private:
    ClickHandler clickHandler;
};

int main() {
    Button button;

    // Set a click handler using a lambda expression
    button.setClickHandler([]() {
        std::cout << "Button clicked!" << std::endl;
    });

    // Simulate a button click
    button.click(); // Output: Button clicked!

    return 0;
}