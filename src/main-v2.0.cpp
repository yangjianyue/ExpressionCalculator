#include <iostream>
#include "ExpressionCalculator-v2.0"

int main() {
    Calculator calc;
    std::string input;

    std::cout << "Advanced Calculator (type 'exit' to quit)\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit")
            break;

        try {
            double result = calc.evaluate(input);
            std::cout << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}