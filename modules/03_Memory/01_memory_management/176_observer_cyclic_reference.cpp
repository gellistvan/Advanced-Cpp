#include <iostream>
#include <memory>

class Observer : public std::enable_shared_from_this<Observer> {
public:
    void observe(std::shared_ptr<Observer> other) {
        other_observer = other;
    }
    ~Observer() {
        std::cout << "Observer destroyed" << std::endl;
    }

private:
    std::weak_ptr<Observer> other_observer;
};

int main() {
    std::shared_ptr<Observer> obs1 = std::make_shared<Observer>();
    std::shared_ptr<Observer> obs2 = std::make_shared<Observer>();

    obs1->observe(obs2);
    obs2->observe(obs1);

    // Resetting to break the cycle
    obs1.reset();
    obs2.reset();

    return 0;
}