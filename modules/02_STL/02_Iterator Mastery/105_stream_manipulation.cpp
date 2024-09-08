#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

// Function to demonstrate file input/output
void file_stream_manipulation(const std::string& filename) {
    // Write data to a file with formatted output
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        ofs << std::setw(10) << std::left << "ID"
            << std::setw(20) << std::left << "Name"
            << std::setw(10) << std::right << "Score" << std::endl;

        ofs << std::setw(10) << std::left << 1
            << std::setw(20) << std::left << "Alice"
            << std::setw(10) << std::right << std::fixed << std::setprecision(2) << 89.75 << std::endl;

        ofs << std::setw(10) << std::left << 2
            << std::setw(20) << std::left << "Bob"
            << std::setw(10) << std::right << std::fixed << std::setprecision(2) << 95.50 << std::endl;
        ofs.close();
    }

    // Read back data from the file
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
        std::cout << "\nReading from file:" << std::endl;
        std::string line;
        while (std::getline(ifs, line)) {
            std::cout << line << std::endl;
        }
        ifs.close();
    }
}

// Function to demonstrate string stream manipulation
void string_stream_manipulation() {
    // Convert a numeric value to a string using stringstream
    int number = 42;
    std::stringstream ss;
    ss << "The answer is " << number;

    std::string result = ss.str();
    std::cout << "\nStringStream result: " << result << std::endl;

    // Convert a string back to a number
    std::string input_str = "123.45";
    double value;
    std::stringstream(input_str) >> value;

    std::cout << "Converted string \"" << input_str << "\" to double: " << value << std::endl;
}

// Function to demonstrate input stream validation
void input_validation_manipulation() {
    int input_value;
    bool valid_input = false;

    while (!valid_input) {
        std::cout << "\nEnter an integer: ";
        std::cin >> input_value;

        if (std::cin.fail()) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << "Invalid input. Please enter a valid integer.\n";
        } else {
            valid_input = true;
        }
    }

    std::cout << "You entered: " << input_value << std::endl;
}

// Function to demonstrate stream formatting options
void stream_formatting_manipulation() {
    double num1 = 123.45678;
    double num2 = 3.14159;
    double num3 = 1.61803;

    std::cout << "\nOriginal numbers: " << num1 << " " << num2 << " " << num3 << std::endl;

    // Show the numbers with different formatting
    std::cout << "\nFormatted output:\n";
    std::cout << std::fixed << std::setprecision(3);
    std::cout << num1 << " " << num2 << " " << num3 << std::endl;

    // Using scientific notation
    std::cout << std::scientific << std::setprecision(2);
    std::cout << num1 << " " << num2 << " " << num3 << std::endl;

    // Reset to default
    std::cout.unsetf(std::ios::scientific);
    std::cout.precision(6); // Resetting precision
}

// Function to demonstrate stream state flags
void stream_state_flags() {
    std::string input = "123abc";
    int num;

    std::istringstream iss(input);
    iss >> num;

    if (iss.fail()) {
        std::cout << "\nStream failed to convert input to integer." << std::endl;
    } else {
        std::cout << "\nExtracted number from input: " << num << std::endl;
    }

    // Check stream state after failed extraction
    iss.clear();
    std::string remaining;
    iss >> remaining;

    std::cout << "Remaining string after extraction: " << remaining << std::endl;
}

// Function to produce a file with formatted content
void create_file(const std::string& filename) {
    std::ofstream ofs(filename);

    if (!ofs.is_open()) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    // Writing header with proper formatting
    ofs << std::setw(10) << std::left << "ID"
        << std::setw(20) << std::left << "Name"
        << std::setw(10) << std::right << "Score" << std::endl;

    // Writing rows with data
    ofs << std::setw(10) << std::left << 1
        << std::setw(20) << std::left << "Alice"
        << std::setw(10) << std::right << std::fixed << std::setprecision(2) << 89.75 << std::endl;

    ofs << std::setw(10) << std::left << 2
        << std::setw(20) << std::left << "Bob"
        << std::setw(10) << std::right << std::fixed << std::setprecision(2) << 95.50 << std::endl;

    ofs << std::setw(10) << std::left << 3
        << std::setw(20) << std::left << "Charlie"
        << std::setw(10) << std::right << std::fixed << std::setprecision(2) << 78.12 << std::endl;

    ofs << std::setw(10) << std::left << 4
        << std::setw(20) << std::left << "Dana"
        << std::setw(10) << std::right << std::fixed << std::setprecision(2) << 82.45 << std::endl;

    ofs.close();

    std::cout << "File created successfully: " << filename << std::endl;
}



void create_and_print_file(const std::string& filename) {
    std::ofstream ofs(filename);

    if (!ofs.is_open()) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    std::stringstream ss;

    // Demonstrating multiple stream manipulators
    std::cout <<"=== Demonstrating std::fixed and std::setprecision ===" << std::endl;
    double pi = 3.1415926535;
    ss << "PI (default): " << pi << '\n';
    ss << std::fixed << std::setprecision(4) << "PI (fixed, precision 4): " << pi << '\n';
    ss << std::setprecision(2) << "PI (fixed, precision 2): " << pi << "\n\n";
    std::cout << ss.str() << std::endl;
    ss.str("");

    std::cout << "=== Demonstrating std::scientific ===" << std::endl;
    ss << std::scientific << std::setprecision(4) << "PI (scientific, precision 4): " << pi << "\n\n";
    std::cout << ss.str() << std::endl;
    ss.str("");

    std::cout << "=== Demonstrating std::hex, std::oct, std::dec ===" << std::endl;
    int num = 255;
    ss << "Decimal: " << num << '\n';
    ss << std::hex << "Hexadecimal: " << num << '\n';
    ss << std::oct << "Octal: " << num << "\n\n";
    std::cout << ss.str() << std::endl;
    ss.str("");

    std::cout <<  "=== Demonstrating std::showpos and std::noshowpos ===" << std::endl;
    int pos_num = 42;
    ss << std::showpos << "Positive number with sign: " << pos_num << '\n';
    ss << std::noshowpos << "Positive number without sign: " << pos_num << "\n\n";
    std::cout << ss.str() << std::endl;
    ss.str("");

    std::cout << "=== Demonstrating std::uppercase and std::nouppercase ===" << std::endl;
    ss << std::uppercase << "Hexadecimal uppercase: " << std::hex << num << '\n';
    ss << std::nouppercase << "Hexadecimal lowercase: " << std::hex << num << "\n\n";
    std::cout << ss.str() << std::endl;
    ss.str("");

    std::cout << "=== Demonstrating std::boolalpha and std::noboolalpha ===" << std::endl;
    bool flag = true;
    ss << std::boolalpha << "Boolean as text: " << flag << '\n';
    ss << std::noboolalpha << "Boolean as number: " << flag << "\n\n";
    std::cout << ss.str() << std::endl;
    ss.str("");
}


int main() {

    // 0. Write file with dummy data
    std::string path {"/tmp/file.txt"};
    create_file(path);

    // 1. Demonstrating file stream manipulation
    file_stream_manipulation(path);

    // 2. Demonstrating string stream manipulation
    string_stream_manipulation();

    // 3. Demonstrating input validation manipulation
    input_validation_manipulation();

    // 4. Demonstrating stream formatting manipulation
    stream_formatting_manipulation();

    // 5. Demonstrating stream state flags
    stream_state_flags();

    create_and_print_file("/tmp/file2.txt");

    return 0;
}
