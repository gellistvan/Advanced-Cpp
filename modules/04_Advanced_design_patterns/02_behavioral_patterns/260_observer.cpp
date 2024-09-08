#include <vector>
#include <memory>
#include <iostream>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float temperature) = 0;
};

class Subject {
public:
    virtual ~Subject() = default;

    void attach(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notify(float temperature) {
        for (const auto& observer : observers) {
            observer->update(temperature);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
};

class WeatherStation : public Subject {
public:
    void setTemperature(float temperature) {
        this->temperature = temperature;
        notify(temperature);
    }

private:
    float temperature;
};

class CurrentConditionsDisplay : public Observer {
public:
    void update(float temperature) override {
        std::cout << "Current conditions: " << temperature << "°C" << std::endl;
    }
};

class StatisticsDisplay : public Observer {
public:
    void update(float temperature) override {
        totalTemperature += temperature;
        ++numReadings;
        float avgTemperature = totalTemperature / numReadings;
        std::cout << "Average temperature: " << avgTemperature << "°C" << std::endl;
    }

private:
    float totalTemperature = 0;
    int numReadings = 0;
};

int main() {
    std::shared_ptr<WeatherStation> weatherStation = std::make_shared<WeatherStation>();

    std::shared_ptr<CurrentConditionsDisplay> currentDisplay = std::make_shared<CurrentConditionsDisplay>();
    std::shared_ptr<StatisticsDisplay> statisticsDisplay = std::make_shared<StatisticsDisplay>();

    weatherStation->attach(currentDisplay);
    weatherStation->attach(statisticsDisplay);

    weatherStation->setTemperature(25.0);
    weatherStation->setTemperature(26.5);
    weatherStation->setTemperature(27.3);

    weatherStation->detach(currentDisplay);

    weatherStation->setTemperature(28.1);

    return 0;
}
