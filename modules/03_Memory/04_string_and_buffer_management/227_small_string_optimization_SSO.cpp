#include <iostream>
#include <cstring>
#include <utility>

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

int main() {
    SSOString s1("short");
    SSOString s2("this is a much longer string that exceeds the SSO threshold");

    std::cout << "s1: " << s1.c_str() << " (size: " << s1.size() << ")" << std::endl;
    std::cout << "s2: " << s2.c_str() << " (size: " << s2.size() << ")" << std::endl;

    return 0;
}