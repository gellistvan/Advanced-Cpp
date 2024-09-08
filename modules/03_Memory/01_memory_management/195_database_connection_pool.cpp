#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

class DatabaseConnection {
public:
    DatabaseConnection(int id) : id(id) {
        std::cout << "DatabaseConnection constructed with ID: " << id << std::endl;
    }

    ~DatabaseConnection() {
        std::cout << "DatabaseConnection destroyed with ID: " << id << std::endl;
    }

    void reset(int newId) {
        id = newId;
        std::cout << "DatabaseConnection reset with new ID: " << id << std::endl;
    }

    int getId() const {
        return id;
    }

private:
    int id;
};

class DatabaseConnectionPool {
public:
    DatabaseConnectionPool(size_t poolSize) {
        for (size_t i = 0; i < poolSize; ++i) {
            pool.push_back(std::make_unique<DatabaseConnection>(i));
        }
    }

    DatabaseConnection* acquireConnection() {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (pool.empty()) {
            throw std::runtime_error("No available connections in the pool");
        }
        DatabaseConnection* connection = pool.back().release();
        pool.pop_back();
        return connection;
    }

    void releaseConnection(DatabaseConnection* connection) {
        std::lock_guard<std::mutex> lock(poolMutex);
        pool.push_back(std::unique_ptr<DatabaseConnection>(connection));
    }

private:
    std::vector<std::unique_ptr<DatabaseConnection>> pool;
    std::mutex poolMutex;
};

int main() {
    const size_t poolSize = 5;
    DatabaseConnectionPool pool(poolSize);

    // Acquire and release connections from the pool
    DatabaseConnection* connection1 = pool.acquireConnection();
    DatabaseConnection* connection2 = pool.acquireConnection();
    pool.releaseConnection(connection1);
    DatabaseConnection* connection3 = pool.acquireConnection();
    connection3->reset(10);

    std::cout << "Database connection pool pattern example executed successfully." << std::endl;

    // Clean up
    pool.releaseConnection(connection2);
    pool.releaseConnection(connection3);

    return 0;
}