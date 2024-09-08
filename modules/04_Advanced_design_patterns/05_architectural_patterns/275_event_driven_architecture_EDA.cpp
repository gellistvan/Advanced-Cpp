#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <vector>

// Event class
class Event {
public:
    std::string type;
    std::string data;

    Event(const std::string& type, const std::string& data)
        : type(type), data(data) {}
};

// EventBus class for handling event publishing and subscribing
class EventBus {
public:
    using EventHandler = std::function<void(const Event&)>;

    void subscribe(const std::string& eventType, EventHandler handler) {
        handlers[eventType].push_back(handler);
    }

    void publish(const Event& event) {
        if (handlers.find(event.type) != handlers.end()) {
            for (const auto& handler : handlers[event.type]) {
                handler(event);
            }
        }
    }

private:
    std::map<std::string, std::vector<EventHandler>> handlers;
};

// OrderService class
class OrderService {
public:
    OrderService(EventBus& eventBus) : eventBus(eventBus) {}

    void createOrder(const std::string& orderId, const std::string& productId) {
        std::cout << "Order created: Order ID " << orderId << ", Product ID " << productId << std::endl;

        // Produce event
        Event event("OrderCreated", "Order ID: " + orderId + ", Product ID: " + productId);

        // Publish event to EventBus
        eventBus.publish(event);
    }

private:
    EventBus& eventBus;
};

// InventoryService class
class InventoryService {
public:
    InventoryService(EventBus& eventBus) {
        eventBus.subscribe("OrderCreated", [this](const Event& event) {
            handleEvent(event);
        });
    }

    void handleEvent(const Event& event) {
        std::cout << "InventoryService received event: " << event.data << std::endl;
        // Update inventory logic here
    }
};

// NotificationService class
class NotificationService {
public:
    NotificationService(EventBus& eventBus) {
        eventBus.subscribe("OrderCreated", [this](const Event& event) {
            handleEvent(event);
        });
    }

    void handleEvent(const Event& event) {
        std::cout << "NotificationService received event: " << event.data << std::endl;
        // Send notification logic here
    }
};

// Main function to demonstrate the EDA system
int main() {
    // Create EventBus
    EventBus eventBus;

    // Create services and subscribe to events
    OrderService orderService(eventBus);
    InventoryService inventoryService(eventBus);
    NotificationService notificationService(eventBus);

    // Simulate creating an order, which triggers events in other services
    orderService.createOrder("12345", "ABC-123");

    return 0;
}
