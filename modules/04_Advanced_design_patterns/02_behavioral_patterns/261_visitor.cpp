#include <iostream>
#include <vector>
#include <memory>

class Circle;
class Rectangle;
class Triangle;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rectangle) = 0;
    virtual void visit(Triangle& triangle) = 0;
};

class Element {
public:
    virtual ~Element() = default;
    virtual void accept(Visitor& visitor) = 0;
};

class Circle : public Element {
public:
    Circle(double radius) : radius(radius) {}

    double getRadius() const { return radius; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double radius;
};

class Rectangle : public Element {
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    double getWidth() const { return width; }
    double getHeight() const { return height; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double width;
    double height;
};

class Triangle : public Element {
public:
    Triangle(double base, double height) : base(base), height(height) {}

    double getBase() const { return base; }
    double getHeight() const { return height; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double base;
    double height;
};

class AreaVisitor : public Visitor {
public:
    void visit(Circle& circle) override {
        double area = 3.14159 * circle.getRadius() * circle.getRadius();
        std::cout << "Circle area: " << area << std::endl;
    }

    void visit(Rectangle& rectangle) override {
        double area = rectangle.getWidth() * rectangle.getHeight();
        std::cout << "Rectangle area: " << area << std::endl;
    }

    void visit(Triangle& triangle) override {
        double area = 0.5 * triangle.getBase() * triangle.getHeight();
        std::cout << "Triangle area: " << area << std::endl;
    }
};

class DrawVisitor : public Visitor {
public:
    void visit(Circle& circle) override {
        std::cout << "Drawing a circle with radius " << circle.getRadius() << std::endl;
    }

    void visit(Rectangle& rectangle) override {
        std::cout << "Drawing a rectangle with width " << rectangle.getWidth() << " and height " << rectangle.getHeight() << std::endl;
    }

    void visit(Triangle& triangle) override {
        std::cout << "Drawing a triangle with base " << triangle.getBase() << " and height " << triangle.getHeight() << std::endl;
    }
};

int main() {
    std::vector<std::shared_ptr<Element>> shapes;
    shapes.push_back(std::make_shared<Circle>(5.0));
    shapes.push_back(std::make_shared<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_shared<Triangle>(3.0, 7.0));

    AreaVisitor areaVisitor;
    DrawVisitor drawVisitor;

    for (auto& shape : shapes) {
        shape->accept(areaVisitor);
        shape->accept(drawVisitor);
    }

    return 0;
}