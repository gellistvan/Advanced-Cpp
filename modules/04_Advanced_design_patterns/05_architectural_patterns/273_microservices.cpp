#include <string>
#include <vector>
#include <iostream>

struct Product {
    int id;
    std::string name;
    double price;
};

class ProductService {
public:
    std::vector<Product> listProducts() {
        return {
                {1, "Laptop", 999.99},
                {2, "Smartphone", 499.99},
                {3, "Tablet", 299.99}
        };
    }

    Product getProduct(int productId) {
        auto products = listProducts();
        for (const auto& product : products) {
            if (product.id == productId) {
                return product;
            }
        }
        throw std::runtime_error("Product not found");
    }
};


struct Order {
    int id;
    int productId;
    int userId;
    std::string status;
};

class OrderService {
public:
    std::vector<Order> listOrders() {
        return {
                {1, 1, 1, "Pending"},
                {2, 2, 2, "Shipped"}
        };
    }
    void createOrder(int productId, int userId) {
        // In a real application, this would persist the order to a database.
        std::cout << "Order created: Product ID " << productId << ", User ID " << userId << std::endl;
    }
};

struct User {
    int id;
    std::string name;
};

class UserService {
public:
    std::vector<User> listUsers() {
        return {
                {1, "Alice"},
                {2, "Bob"}
        };
    }
    User getUser(int userId) {
        auto users = listUsers();
        for (const auto& user : users) {
            if (user.id == userId) {
                return user;
            }
        }
        throw std::runtime_error("User not found");
    }

};

// Simulated microservice interaction
int main() {
    ProductService productService;
    OrderService orderService;
    UserService userService;

    // List all products
    std::cout << "Available Products:\n";
    auto products = productService.listProducts();
    for (const auto& product : products) {
        std::cout << "ID: " << product.id << ", Name: " << product.name
                  << ", Price: $" << product.price << std::endl;
    }

    // Create an order for Alice for the first product (Laptop)
    int userId = 1;  // Assuming Alice's user ID is 1
    int productId = 1;  // Assuming Laptop's product ID is 1

    try {
        User user = userService.getUser(userId);
        Product product = productService.getProduct(productId);
        std::cout << "\nCreating an order for " << user.name
                  << " for the product " << product.name << "...\n";
        orderService.createOrder(product.id, user.id);
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    // List all orders
    std::cout << "\nCurrent Orders:\n";
    auto orders = orderService.listOrders();
    for (const auto& order : orders) {
        std::cout << "Order ID: " << order.id << ", Product ID: " << order.productId
                  << ", User ID: " << order.userId << ", Status: " << order.status << std::endl;
    }

    return 0;
}