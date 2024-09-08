#include <string>
#include <vector>
#include <iostream>

struct Customer {
    int id;
    std::string name;
};

class ICustomerService {
public:
    virtual ~ICustomerService() = default;
    virtual Customer getCustomer(int customerId) = 0;
    virtual std::vector<Customer> listCustomers() = 0;
};

struct Product {
    int id;
    std::string name;
    double price;
};

class IProductService {
public:
    virtual ~IProductService() = default;
    virtual Product getProduct(int productId) = 0;
    virtual std::vector<Product> listProducts() = 0;
};


struct Order {
    int id;
    int customerId;
    int productId;
    std::string status;
};

class IOrderService {
public:
    virtual ~IOrderService() = default;
    virtual Order getOrder(int orderId) = 0;
    virtual void createOrder(int customerId, int productId) = 0;
    virtual std::vector<Order> listOrders() = 0;
};

class CustomerService : public ICustomerService {
public:
    Customer getCustomer(int customerId) override {
        auto customers = listCustomers();
        for (const auto& customer : customers) {
            if (customer.id == customerId) {
                return customer;
            }
        }
        throw std::runtime_error("Customer not found");
    }

    std::vector<Customer> listCustomers() override  {
        return {
            {1, "Alice"},
            {2, "Bob"}
        };
    }
};

class ProductService : public IProductService {
public:
    Product getProduct(int productId) override {
        auto products = listProducts();
        for (const auto& product : products) {
            if (product.id == productId) {
                return product;
            }
        }
        throw std::runtime_error("Product not found");
    }

    std::vector<Product> listProducts() override {
        return {
            {1, "Laptop", 999.99},
            {2, "Smartphone", 499.99},
            {3, "Tablet", 299.99}
        };
    }
};


class OrderService : public IOrderService {
public:
    Order getOrder(int orderId) override {
        auto orders = listOrders();
        for (const auto& order : orders) {
            if (order.id == orderId) {
                return order;
            }
        }
        throw std::runtime_error("Order not found");
    }

    void createOrder(int customerId, int productId) override  {
        // In a real application, this would persist the order to a database.
        std::cout << "Order created: Customer ID " << customerId << ", Product ID " << productId << std::endl;
    }

    std::vector<Order> listOrders() override {
        return {
            {1, 1, 1, "Pending"},
            {2, 2, 2, "Shipped"}
        };
    }
};

int main() {
    // Initialize services
    CustomerService customerService;
    ProductService productService;
    OrderService orderService;

    // Mimic service calls in SOA
    try {
        // Fetch and display a customer
        Customer customer = customerService.getCustomer(1);
        std::cout << "Customer fetched: ID " << customer.id << ", Name: " << customer.name << std::endl;

        // Fetch and display a product
        Product product = productService.getProduct(1);
        std::cout << "Product fetched: ID " << product.id << ", Name: " << product.name << ", Price: $" << product.price << std::endl;

        // Create a new order
        orderService.createOrder(customer.id, product.id);

        // Fetch and display all orders
        std::vector<Order> orders = orderService.listOrders();
        for (const auto& order : orders) {
            std::cout << "Order ID: " << order.id << ", Customer ID: " << order.customerId
                      << ", Product ID: " << order.productId << ", Status: " << order.status << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
