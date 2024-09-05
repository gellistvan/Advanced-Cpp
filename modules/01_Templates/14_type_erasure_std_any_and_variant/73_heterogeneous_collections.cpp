#include <iostream>
#include <memory>
#include <vector>

class IShape {
public:
    virtual ~IShape() = default;
    virtual void draw() const = 0;
    virtual void resize(double factor) = 0;
};

class Circle : public IShape {
public:
    void draw() const override {
        std::cout << "Drawing Circle" << std::endl;
    }

    void resize(double factor) override {
        std::cout << "Resizing Circle by factor " << factor << std::endl;
    }
};

class Square : public IShape {
public:
    void draw() const override {
        std::cout << "Drawing Square" << std::endl;
    }

    void resize(double factor) override {
        std::cout << "Resizing Square by factor " << factor << std::endl;
    }
};

class Shape {
public:
    template <typename T>
    Shape(T shape) : impl(std::make_shared<Model<T>>(std::move(shape))) {}

    void draw() const {
        impl->draw();
    }

    void resize(double factor) {
        impl->resize(factor);
    }

private:
    struct Concept {
        virtual ~Concept() = default;
        virtual void draw() const = 0;
        virtual void resize(double factor) = 0;
    };

    template <typename T>
    struct Model : Concept {
        Model(T shape) : shape(std::move(shape)) {}

        void draw() const override {
            shape.draw();
        }

        void resize(double factor) override {
            shape.resize(factor);
        }

        T shape;
    };

    std::shared_ptr<Concept> impl;
};

int main() {
    std::vector<std::shared_ptr<IShape>> shapes;
    shapes.push_back(std::make_shared<Circle>());
    shapes.push_back(std::make_shared<Square>());

    for (const auto& shape : shapes) {
        shape->draw();
        shape->resize(1.5);
    }

    // Output:
    // Drawing Circle
    // Resizing Circle by factor 1.5
    // Drawing Square
    // Resizing Square by factor 1.5

    return 0;
}