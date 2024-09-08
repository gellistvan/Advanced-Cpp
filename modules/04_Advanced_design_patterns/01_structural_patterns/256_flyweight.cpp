#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

// Flyweight class
class Character {
private:
    char symbol; // Intrinsic state

public:
    Character(char symbol) : symbol(symbol) {}

    void display(int fontSize) const {
        std::cout << "Character: " << symbol << ", Font size: " << fontSize << std::endl;
    }

    char getSymbol() const {
        return symbol;
    }
};

class CharacterFactory {
private:
    std::unordered_map<char, std::shared_ptr<Character>> characters; // Cache of flyweights

public:
    std::shared_ptr<Character> getCharacter(char symbol) {
        // Check if the character is already created
        auto it = characters.find(symbol);
        if (it != characters.end()) {
            return it->second;
        }

        // Create a new character and add it to the cache
        std::shared_ptr<Character> character = std::make_shared<Character>(symbol);
        characters[symbol] = character;
        return character;
    }
};

int main() {
    CharacterFactory factory;

    // Create characters
    std::shared_ptr<Character> charA1 = factory.getCharacter('A');
    std::shared_ptr<Character> charA2 = factory.getCharacter('A');
    std::shared_ptr<Character> charB = factory.getCharacter('B');

    // Display characters with different font sizes
    charA1->display(12);
    charA2->display(14);
    charB->display(16);

    // Check if charA1 and charA2 are the same object
    if (charA1 == charA2) {
        std::cout << "charA1 and charA2 are the same object" << std::endl;
    } else {
        std::cout << "charA1 and charA2 are different objects" << std::endl;
    }

    return 0;
}
