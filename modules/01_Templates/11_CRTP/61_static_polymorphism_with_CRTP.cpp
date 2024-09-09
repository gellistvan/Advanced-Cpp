#include <iostream>
#include <vector>
#include <variant>

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

using ShapeVariant = std::variant<Circle, Square>;

int main() {
    Circle circle;
    Square square;

    circle.draw();   // Output: Drawing Circle
    square.draw();   // Output: Drawing Square

    circle.resize(2.0); // Output: Resizing Circle by factor 2
    square.resize(3.0); // Output: Resizing Square by factor 3

    std::vector<ShapeVariant> shapes;

    // Add Sphere and Square to the vector
    shapes.emplace_back(Circle{});
    shapes.emplace_back(Square{});

    // Iterate over the shapes and call draw() directly
    for (const auto& shape : shapes) {
        std::visit([](const auto& s) { s.draw(); }, shape);
    }

    return 0;
}