#include <iostream>
#include <memory>

// Implementation interface
class DrawingAPI {
public:
    virtual void drawCircle(double x, double y, double radius) const = 0;
    virtual ~DrawingAPI() = default;
};

// Concrete implementation for Windows
class WindowsAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) const override {
        std::cout << "Drawing circle on Windows at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
};

// Concrete implementation for Linux
class LinuxAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) const override {
        std::cout << "Drawing circle on Linux at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
};

// Abstraction interface
class Shape {
protected:
    std::shared_ptr<DrawingAPI> drawingAPI;

public:
    Shape(std::shared_ptr<DrawingAPI> drawingAPI) : drawingAPI(drawingAPI) {}

    virtual void draw() const = 0;
    virtual void resizeByPercentage(double percent) = 0;
    virtual ~Shape() = default;
};

// Concrete abstraction for Circle
class CircleShape : public Shape {
private:
    double x, y, radius;

public:
    CircleShape(double x, double y, double radius, std::shared_ptr<DrawingAPI> drawingAPI)
        : Shape(drawingAPI), x(x), y(y), radius(radius) {}

    void draw() const override {
        drawingAPI->drawCircle(x, y, radius);
    }

    void resizeByPercentage(double percent) override {
        radius *= (1 + percent / 100);
    }
};


int main() {
    // Create platform-specific drawing APIs
    std::shared_ptr<DrawingAPI> windowsAPI = std::make_shared<WindowsAPI>();
    std::shared_ptr<DrawingAPI> linuxAPI = std::make_shared<LinuxAPI>();

    // Create shapes with different implementations
    CircleShape circle1(1, 2, 3, windowsAPI);
    CircleShape circle2(4, 5, 6, linuxAPI);

    // Draw shapes
    circle1.draw();
    circle2.draw();

    // Resize and draw again
    circle1.resizeByPercentage(50);
    circle1.draw();

    return 0;
}
