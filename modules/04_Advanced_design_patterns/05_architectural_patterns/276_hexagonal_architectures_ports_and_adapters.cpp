#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdexcept>

// Domain model
class Product {
public:
    int id;
    std::string name;
    double price;

    Product() : id(0), name(""), price(0.0) {}

    Product(int id, const std::string& name, double price)
        : id(id), name(name), price(price) {}
};

// Port: Product repository interface
class IProductRepository {
public:
    virtual ~IProductRepository() = default;
    virtual void addProduct(const Product& product) = 0;
    virtual Product getProduct(int productId) = 0;
    virtual std::vector<Product> listProducts() = 0;
};

// Port: Product service interface
class IProductService {
public:
    virtual ~IProductService() = default;
    virtual void createProduct(const Product& product) = 0;
    virtual Product fetchProduct(int productId) = 0;
    virtual std::vector<Product> fetchAllProducts() = 0;
};

// Application Service
class ProductService : public IProductService {
    IProductRepository& productRepository;

public:
    ProductService(IProductRepository& repo) : productRepository(repo) {}

    void createProduct(const Product& product) override {
        productRepository.addProduct(product);
    }

    Product fetchProduct(int productId) override {
        return productRepository.getProduct(productId);
    }

    std::vector<Product> fetchAllProducts() override {
        return productRepository.listProducts();
    }
};

// Adapter: In-memory product repository
class InMemoryProductRepository : public IProductRepository {
    std::unordered_map<int, Product> products;

public:
    void addProduct(const Product& product) override {
        products[product.id] = product;
    }

    Product getProduct(int productId) override {
        if (products.find(productId) != products.end()) {
            return products[productId];
        }
        throw std::runtime_error("Product not found");
    }

    std::vector<Product> listProducts() override {
        std::vector<Product> productList;
        for (const auto& [id, product] : products) {
            productList.push_back(product);
        }
        return productList;
    }
};

// Adapter: Command-Line Interface (CLI)
class CLIAdapter {
    IProductService& productService;

public:
    CLIAdapter(IProductService& service) : productService(service) {}

    void start() {
        bool running = true;
        while (running) {
            std::cout << "\n=== Product Management ===\n";
            std::cout << "1. Add Product\n";
            std::cout << "2. List Products\n";
            std::cout << "3. Get Product\n";
            std::cout << "4. Exit\n";
            std::cout << "Choose an option: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    addProduct();
                    break;
                case 2:
                    listProducts();
                    break;
                case 3:
                    getProduct();
                    break;
                case 4:
                    running = false;
                    break;
                default:
                    std::cout << "Invalid option.\n";
                    break;
            }
        }
    }

private:
    void addProduct() {
        int id;
        std::string name;
        double price;

        std::cout << "Enter Product ID: ";
        std::cin >> id;
        std::cin.ignore(); // Ignore remaining newline

        std::cout << "Enter Product Name: ";
        std::getline(std::cin, name);

        std::cout << "Enter Product Price: ";
        std::cin >> price;

        Product product(id, name, price);
        productService.createProduct(product);

        std::cout << "Product added successfully!\n";
    }

    void listProducts() {
        auto products = productService.fetchAllProducts();
        std::cout << "\n--- Product List ---\n";
        for (const auto& product : products) {
            std::cout << "ID: " << product.id << ", Name: " << product.name << ", Price: $" << product.price << "\n";
        }
    }

    void getProduct() {
        int id;
        std::cout << "Enter Product ID: ";
        std::cin >> id;

        try {
            Product product = productService.fetchProduct(id);
            std::cout << "\n--- Product Details ---\n";
            std::cout << "ID: " << product.id << ", Name: " << product.name << ", Price: $" << product.price << "\n";
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
};

int main() {
    InMemoryProductRepository productRepository;
    ProductService productService(productRepository);
    CLIAdapter cliAdapter(productService);

    cliAdapter.start();
    return 0;
}
