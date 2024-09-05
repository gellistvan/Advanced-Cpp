#include <functional>
#include <iostream>
#include <string>
#include <vector>

class Processor {
public:
    using Step = std::function<std::string(const std::string&)>;

    void addStep(Step step) {
        steps.push_back(std::move(step));
    }

    std::string process(const std::string& input) const {
        std::string result = input;
        for (const auto& step : steps) {
            result = step(result);
        }
        return result;
    }

private:
    std::vector<Step> steps;
};

int main() {
    Processor processor;

    // Add steps to the processor pipeline
    processor.addStep([](const std::string& input) {
        return input + " Step 1";
    });
    processor.addStep([](const std::string& input) {
        return input + " -> Step 2";
    });
    processor.addStep([](const std::string& input) {
        return input + " -> Step 3";
    });

    // Process an input string through the pipeline
    std::string result = processor.process("Start");
    std::cout << "Result: " << result << std::endl; // Output: Result: Start Step 1 -> Step 2 -> Step 3

    return 0;
}