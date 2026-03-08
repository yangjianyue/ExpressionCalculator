#include <iostream>
#include <string>
#include "ExpressionCalculator-v2.0.h"

int main() {

    ExpressionCalculator calc;
    std::string line;

    std::cout << "Advanced Calculator (supports ** power)\n";

    while (true) {

        std::cout << "> ";
        std::getline(std::cin, line);

        if (line == "exit")
            break;

        try {
            double result = calc.evaluate(line);
            std::cout << result << std::endl;
        }

        catch (std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}