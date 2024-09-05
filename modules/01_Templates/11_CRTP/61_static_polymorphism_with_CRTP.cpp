#include <iostream>

template <typename Derived>
class Shape {
public:
    void draw() const {
        static_cast<const Derived*>(this)->draw();
    }

    void resize(double factor) {
        static_cast<Derived*>(this)->resize(factor);
    }
};

class Circle : public Shape<Circle> {
public:
    void draw() const {
        std::cout << "Drawing Circle" << std::endl;
    }

    void resize(double factor) {
        std::cout << "Resizing Circle by factor " << factor << std::endl;
    }
};

class Square : public Shape<Square> {
public:
    void draw() const {
        std::cout << "Drawing Square" << std::endl;
    }

    void resize(double factor) {
        std::cout << "Resizing Square by factor " << factor << std::endl;
    }
};

int main() {
    Circle circle;
    Square square;

    circle.draw();   // Output: Drawing Circle
    square.draw();   // Output: Drawing Square

    circle.resize(2.0); // Output: Resizing Circle by factor 2
    square.resize(3.0); // Output: Resizing Square by factor 3

    return 0;
}