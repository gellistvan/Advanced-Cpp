#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual void resize(double factor) = 0;
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle" << std::endl;
    }

    void resize(double factor) override {
        std::cout << "Resizing Circle by factor " << factor << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Square" << std::endl;
    }

    void resize(double factor) override {
        std::cout << "Resizing Square by factor " << factor << std::endl;
    }
};

int main() {
    Shape* shapes[] = {new Circle(), new Square()};

    for (Shape* shape : shapes) {
        shape->draw();
        shape->resize(2.0);
        delete shape;
    }

    return 0;
}