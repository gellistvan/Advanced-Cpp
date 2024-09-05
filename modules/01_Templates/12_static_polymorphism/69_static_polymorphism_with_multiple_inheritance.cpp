#include <iostream>
#include <string>

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


template <typename Derived>
class Colorable {
public:
    void setColor(const std::string& color) {
        static_cast<Derived*>(this)->setColorImpl(color);
    }

    std::string getColor() const {
        return static_cast<const Derived*>(this)->getColorImpl();
    }
};

class Circle : public Shape<Circle>, public Colorable<Circle> {
public:
    void draw() const {
        std::cout << "Drawing Circle" << std::endl;
    }

    void resize(double factor) {
        std::cout << "Resizing Circle by factor " << factor << std::endl;
    }

    void setColorImpl(const std::string& color) {
        this->color = color;
    }

    std::string getColorImpl() const {
        return color;
    }

private:
    std::string color;
};

class Square : public Shape<Square>, public Colorable<Square> {
public:
    void draw() const {
        std::cout << "Drawing Square" << std::endl;
    }

    void resize(double factor) {
        std::cout << "Resizing Square by factor " << factor << std::endl;
    }

    void setColorImpl(const std::string& color) {
        this->color = color;
    }

    std::string getColorImpl() const {
        return color;
    }

private:
    std::string color;
};

int main() {
    Circle circle;
    Square square;

    circle.draw();   // Output: Drawing Circle
    square.draw();   // Output: Drawing Square

    circle.resize(2.0); // Output: Resizing Circle by factor 2
    square.resize(3.0); // Output: Resizing Square by factor 3

    circle.setColor("red");
    square.setColor("blue");

    std::cout << "Circle color: " << circle.getColor() << std::endl; // Output: Circle color: red
    std::cout << "Square color: " << square.getColor() << std::endl; // Output: Square color: blue

    return 0;
}