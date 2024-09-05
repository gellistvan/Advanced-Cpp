#include <iostream>
#include <vector>
#include <memory>

// Base class with virtual functions
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual void resize(double factor) = 0;
};

// Derived class Circle
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle" << std::endl;
    }

    void resize(double factor) override {
        std::cout << "Resizing Circle by factor " << factor << std::endl;
    }
};

// Derived class Square
class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Square" << std::endl;
    }

    void resize(double factor) override {
        std::cout << "Resizing Square by factor " << factor << std::endl;
    }
};

// Polymorphic container using dynamic polymorphism
class ShapeContainer {
public:
    void addShape(std::shared_ptr<Shape> shape) {
        shapes.push_back(std::move(shape));
    }

    void drawAll() const {
        for (const auto& shape : shapes) {
            shape->draw();
        }
    }

    void resizeAll(double factor) {
        for (const auto& shape : shapes) {
            shape->resize(factor);
        }
    }

private:
    std::vector<std::shared_ptr<Shape>> shapes;
};

int main() {
    ShapeContainer container;
    container.addShape(std::make_shared<Circle>());
    container.addShape(std::make_shared<Square>());

    container.drawAll();
    // Output:


    // Drawing Circle
    // Drawing Square

    container.resizeAll(1.5);
    // Output:
    // Resizing Circle by factor 1.5
    // Resizing Square by factor 1.5

    return 0;
}
