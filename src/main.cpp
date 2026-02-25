#include <iostream>
#include "ExpressionCalculator.h"

int main() {
    ExpressionCalculator calc;
    std::string input;

    std::cout << "Expression Calculator (type 'exit' to quit)\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") break;

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