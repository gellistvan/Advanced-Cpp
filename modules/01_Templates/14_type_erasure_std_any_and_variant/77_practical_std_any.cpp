#include <any>
#include <iostream>
#include <string>
#include <unordered_map>

class Settings {
public:
    template <typename T>
    void set(const std::string& key, T value) {
        settings[key] = value;
    }

    template <typename T>
    T get(const std::string& key) const {
        try {
            return std::any_cast<T>(settings.at(key));
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Bad any cast");
        } catch (const std::out_of_range& e) {
            throw std::runtime_error("Key not found");
        }
    }

private:
    std::unordered_map<std::string, std::any> settings;
};

int main() {
    Settings settings;
    settings.set("volume", 10);
    settings.set("username", std::string("admin"));

    std::cout << "Volume: " << settings.get<int>("volume") << std::endl;         // Output: Volume: 10
    std::cout << "Username: " << settings.get<std::string>("username") << std::endl; // Output: Username: admin

    try {
        std::cout << "Brightness: " << settings.get<int>("brightness") << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl; // Output: Key not found
    }

    return 0;
}