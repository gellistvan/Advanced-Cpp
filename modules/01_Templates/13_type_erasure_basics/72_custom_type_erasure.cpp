#include <iostream>
#include <memory>

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
    Shape circle = Circle();
    Shape square = Square();

    circle.draw();   // Output: Drawing Circle
    square.draw();   // Output: Drawing Square

    circle.resize(2.0); // Output: Resizing Circle by factor 2
    square.resize(3.0); // Output: Resizing Square by factor 3

    return 0;
}
