#include <iostream>
#include <vector>
#include <memory>

// Observer Interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

// Subject Class
class Subject {
public:
    void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<Observer> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const std::string& message) {
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
};

// Concrete Observer
class ConcreteObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Observer received message: " << message << std::endl;
    }
};

int main() {
    std::shared_ptr<Subject> subject = std::make_shared<Subject>();

    std::shared_ptr<Observer> observer1 = std::make_shared<ConcreteObserver>();
    std::shared_ptr<Observer> observer2 = std::make_shared<ConcreteObserver>();

    subject->addObserver(observer1);
    subject->addObserver(observer2);

    subject->notifyObservers("State changed");

    subject->removeObserver(observer1);

    subject->notifyObservers("Another state change");

    return 0;
}

