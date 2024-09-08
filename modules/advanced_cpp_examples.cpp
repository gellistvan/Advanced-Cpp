#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdlib>  // for system()
#include <stack>

namespace fs = std::filesystem;

struct DirectoryEntry {
    std::string name;
    std::string path;
    bool is_directory;
};

void list_directory(const std::string& current_path, std::vector<DirectoryEntry>& entries) {
    entries.clear();
    for (const auto& entry : fs::directory_iterator(current_path)) {
        entries.push_back({entry.path().filename().string(), entry.path().string(), entry.is_directory()});
    }
}

void display_menu(const std::vector<DirectoryEntry>& entries) {
    std::cout << "\nCurrent Directory: \n";
    for (size_t i = 0; i < entries.size(); ++i) {
        std::cout << i << ": " << entries[i].name;
        if (entries[i].is_directory) {
            std::cout << "/";
        }
        std::cout << "\n";
    }
    std::cout << "q: Quit, b: Back\n";
}

int main() {
    std::stack<std::string> directory_stack;
    directory_stack.push(fs::current_path().string());

    while (true) {
        std::string current_path = directory_stack.top();
        std::vector<DirectoryEntry> entries;
        list_directory(current_path, entries);
        display_menu(entries);

        std::cout << "Select an option: ";
        char input;
        std::cin >> input;

        if (input == 'q' || input == 'Q') {
            std::cout << "Exiting.\n";
            break;
        } else if (input == 'b' || input == 'B') {
            if (directory_stack.size() > 1) {
                directory_stack.pop();
            } else {
                std::cout << "Already in the top directory.\n";
            }
        } else if (isdigit(input)) {
            int index = input - '0';
            if (index >= 0 && index < entries.size()) {
                if (entries[index].is_directory) {
                    directory_stack.push(entries[index].path);
                } else {
                    std::cout << "Executing: " << entries[index].name << "\n";
                    std::system(entries[index].path.c_str());
                }
            } else {
                std::cout << "Invalid index.\n";
            }
        }
    }

    return 0;
}
