#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>

// Message Broker
class MessageBroker {
public:
    using Callback = std::function<void(const std::string&)>;
    using SubscriberId = int;

    SubscriberId subscribe(const std::string& topic, Callback callback) {
        subscribers[topic].emplace_back(nextSubscriberId, callback);
        return nextSubscriberId++;
    }

    void unsubscribe(const std::string& topic, SubscriberId id) {
        auto& subs = subscribers[topic];
        subs.erase(std::remove_if(subs.begin(), subs.end(),
                                  [id](const auto& pair) { return pair.first == id; }),
                   subs.end());
    }

    void publish(const std::string& topic, const std::string& message) {
        for (const auto& [id, callback] : subscribers[topic]) {
            callback(message);
        }
    }

private:
    std::unordered_map<std::string, std::vector<std::pair<SubscriberId, Callback>>> subscribers;
    SubscriberId nextSubscriberId = 0;
};

// Publisher Class
class Publisher {
public:
    Publisher(MessageBroker& broker) : broker(broker) {}

    void publish(const std::string& topic, const std::string& message) {
        broker.publish(topic, message);
    }

private:
    MessageBroker& broker;
};

// Subscriber Class
class Subscriber {
public:
    Subscriber(MessageBroker& broker) : broker(broker) {}

    void subscribe(const std::string& topic) {
        id = broker.subscribe(topic, [this](const std::string& message) { receive(message); });
    }

    void unsubscribe(const std::string& topic) {
        broker.unsubscribe(topic, id);
    }

    void receive(const std::string& message) {
        std::cout << "Subscriber received message: " << message << std::endl;
    }

private:
    MessageBroker& broker;
    MessageBroker::SubscriberId id;
};

int main() {
    MessageBroker broker;

    Publisher publisher(broker);
    Subscriber subscriber1(broker);
    Subscriber subscriber2(broker);

    subscriber1.subscribe("news");
    subscriber2.subscribe("news");

    publisher.publish("news", "Breaking news!");

    subscriber1.unsubscribe("news");

    publisher.publish("news", "More news!");

    return 0;
}
