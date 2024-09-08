#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>

class SSOString {
    static constexpr size_t SSO_THRESHOLD = 15;

    union {
        char small[SSO_THRESHOLD + 1];
        struct {
            char* data;
            size_t size;
            size_t capacity;
        } large;
    };

    bool isSmall() const {
        return small[SSO_THRESHOLD] == 0;
    }

public:
    SSOString() {
        small[0] = '\0';
        small[SSO_THRESHOLD] = 0;
    }

    SSOString(const char* str) {
        size_t len = std::strlen(str);
        if (len <= SSO_THRESHOLD) {
            std::strcpy(small, str);
            small[SSO_THRESHOLD] = 0;
        } else {
            large.size = len;
            large.capacity = len;
            large.data = new char[len + 1];
            std::strcpy(large.data, str);
            small[SSO_THRESHOLD] = 1;
        }
    }

    SSOString(const SSOString& other) {
        if (other.isSmall()) {
            std::strcpy(small, other.small);
            small[SSO_THRESHOLD] = 0;
        } else {
            large.size = other.large.size;
            large.capacity = other.large.capacity;
            large.data = new char[large.size + 1];
            std::strcpy(large.data, other.large.data);
            small[SSO_THRESHOLD] = 1;
        }
    }

    SSOString(SSOString&& other) noexcept {
        if (other.isSmall()) {
            std::strcpy(small, other.small);
            small[SSO_THRESHOLD] = 0;
        } else {
            large = other.large;
            other.large.data = nullptr;
            small[SSO_THRESHOLD] = 1;
        }
    }

    SSOString& operator=(SSOString other) {
        swap(*this, other);
        return *this;
    }

    ~SSOString() {
        if (!isSmall() && large.data) {
            delete[] large.data;
        }
    }

    size_t size() const {
        return isSmall() ? std::strlen(small) : large.size;
    }

    const char* c_str() const {
        return isSmall() ? small : large.data;
    }

    friend void swap(SSOString& first, SSOString& second) noexcept {
        using std::swap;
        if (first.isSmall() && second.isSmall()) {
            swap(first.small, second.small);
        } else {
            swap(first.large, second.large);
            swap(first.small[SSO_THRESHOLD], second.small[SSO_THRESHOLD]);
        }
    }
};

class Logger {
    std::vector<SSOString> logs;

public:
    void log(const char* message) {
        logs.emplace_back(message);
    }

    void printLogs() const {
        for (const auto& log : logs) {
            std::cout << log.c_str() << std::endl;
        }
    }
};

int main() {
    Logger logger;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 100000; ++i) {
        logger.log("Short log message");
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    // Optionally print logs (can be commented out to save time)
    // logger.printLogs();

    return 0;
}