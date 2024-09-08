#include <iostream>
#include <memory>
#include <string>

// Subject interface
class Image {
public:
    virtual void display() const = 0;
    virtual ~Image() = default;
};

// Real subject
class RealImage : public Image {
private:
    std::string filename;

    void loadImageFromDisk() const {
        std::cout << "Loading image from disk: " << filename << std::endl;
    }

public:
    RealImage(const std::string& filename) : filename(filename) {
        loadImageFromDisk();
    }

    void display() const override {
        std::cout << "Displaying image: " << filename << std::endl;
    }
};

// Proxy
class ProxyImage : public Image {
private:
    std::string filename;
    mutable std::shared_ptr<RealImage> realImage; // Use mutable to allow lazy initialization in const methods

public:
    ProxyImage(const std::string& filename) : filename(filename), realImage(nullptr) {}

    void display() const override {
        if (!realImage) {
            realImage = std::make_shared<RealImage>(filename);
        }
        realImage->display();
    }
};

int main() {
    // Create a proxy for the image
    ProxyImage proxyImage("large_image.jpg");

    // Display the image
    std::cout << "First call to display():" << std::endl;
    proxyImage.display();

    std::cout << "\nSecond call to display():" << std::endl;
    proxyImage.display();

    return 0;
}
