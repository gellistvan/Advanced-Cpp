#include <bitset>
#include <iostream>
#include <map>
#include <string>

int main() {
    // Simplified example: pre-defined Huffman codes
    std::map<char, std::string> huffman_codes;
    huffman_codes['a'] = "00";
    huffman_codes['b'] = "01";
    huffman_codes['c'] = "10";
    huffman_codes['d'] = "110";
    huffman_codes['e'] = "111";

    std::string input = "abcde";
    std::string encoded_string;

    // Encode the input string
    for (char ch : input) {
        encoded_string += huffman_codes[ch];
    }

    // Store the encoded string in a bitset
    std::bitset<32> encoded_bits(encoded_string);

    std::cout << "Encoded string: " << encoded_string << std::endl;
    std::cout << "Encoded bits: " << encoded_bits << std::endl;

    return 0;
}