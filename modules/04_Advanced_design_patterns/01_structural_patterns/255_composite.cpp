#include <iostream>
#include <vector>
#include <memory>

// Abstract base class
class Shape {
public:
    virtual void draw() const = 0; // Pure virtual function
    virtual ~Shape() = default; // Virtual destructor
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Square" << std::endl;
    }
};

class Group : public Shape {
private:
    std::vector<std::shared_ptr<Shape>> shapes; // Vector to hold child shapes
public:
    void addShape(std::shared_ptr<Shape> shape) {
        shapes.push_back(shape);
    }

    void draw() const override {
        std::cout << "Drawing a Group of Shapes:" << std::endl;
        for (const auto& shape : shapes) {
            shape->draw();
        }
    }
};

int main() {
    // Create individual shapes
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>();
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>();
    std::shared_ptr<Shape> square1 = std::make_shared<Square>();

    // Create a group and add shapes to it
    std::shared_ptr<Group> group1 = std::make_shared<Group>();
    group1->addShape(circle1);
    group1->addShape(square1);

    // Create another group and add shapes to it
    std::shared_ptr<Group> group2 = std::make_shared<Group>();
    group2->addShape(circle2);
    group2->addShape(group1); // Adding a group to another group

    // Draw the groups
    group2->draw();

    return 0;
}
