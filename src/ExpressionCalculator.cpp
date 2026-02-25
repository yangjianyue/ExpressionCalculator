#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <sstream>

enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen
};

struct Token {
    TokenType type;
    std::string value;
};

class ExpressionCalculator {
public:
    double evaluate(const std::string & expr) {
        auto tokens = tokenize(expr);
        auto postfix = infixToPostfix(tokens);
        return evaluatePostfix(postfix);
    }

private:
    // ==============================
    // 1. Tokenizer
    // ==============================
    std::vector<Token> tokenize(const std::string & expr) {
        std::vector<Token> tokens;
        for (size_t i = 0; i < expr.size();) {
            if (isspace(expr[i])) {
                ++i;
            }
            else if (isdigit(expr[i]) || expr[i] == '.') {
                std::string number;
                while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                    number += expr[i++];
                }
                tokens.push_back({ TokenType::Number, number });
            }
            else if (expr[i] == '(') {
                tokens.push_back({ TokenType::LeftParen, "(" });
                ++i;
            }
            else if (expr[i] == ')') {
                tokens.push_back({ TokenType::RightParen, ")" });
                ++i;
            }
            else {
                // handle ** operator
                if (expr[i] == '*' && i + 1 < expr.size() && expr[i + 1] == '*') {
                    tokens.push_back({ TokenType::Operator, "**" });
                    i += 2;
                }
                else {
                    std::string op(1, expr[i]);
                    tokens.push_back({ TokenType::Operator, op });
                    ++i;
                }
            }
        }

        handleUnaryOperators(tokens);
        return tokens;
    }

    // 处理一元 + -
    void handleUnaryOperators(std::vector<Token> & tokens) {
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i].type == TokenType::Operator &&
                (tokens[i].value == "-" || tokens[i].value == "+")) {

                if (i == 0 ||
                    tokens[i - 1].type == TokenType::Operator ||
                    tokens[i - 1].type == TokenType::LeftParen) {

                    // 插入 0
                    tokens.insert(tokens.begin() + i, { TokenType::Number, "0" });
                    ++i;
                }
            }
        }
    }

    // ==============================
    // 2. 优先级
    // ==============================
    int precedence(const std::string & op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/" || op == "%") return 2;
        if (op == "^" || op == "**") return 3;
        return 0;
    }

    bool isRightAssociative(const std::string & op) {
        return (op == "^" || op == "**");
    }

    // ==============================
    // 3. 中缀转后缀
    // ==============================
    std::vector<Token> infixToPostfix(const std::vector<Token> & tokens) {
        std::vector<Token> output;
        std::stack<Token> opStack;

        for (const auto& token : tokens) {
            if (token.type == TokenType::Number) {
                output.push_back(token);
            }
            else if (token.type == TokenType::Operator) {
                while (!opStack.empty() &&
                    opStack.top().type == TokenType::Operator &&
                    ((precedence(opStack.top().value) > precedence(token.value)) ||
                        (precedence(opStack.top().value) == precedence(token.value) &&
                            !isRightAssociative(token.value)))) {

                    output.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(token);
            }
            else if (token.type == TokenType::LeftParen) {
                opStack.push(token);
            }
            else if (token.type == TokenType::RightParen) {
                while (!opStack.empty() &&
                    opStack.top().type != TokenType::LeftParen) {
                    output.push_back(opStack.top());
                    opStack.pop();
                }

                if (opStack.empty())
                    throw std::runtime_error("Mismatched parentheses");

                opStack.pop(); // remove '('
            }
        }

        while (!opStack.empty()) {
            if (opStack.top().type == TokenType::LeftParen)
                throw std::runtime_error("Mismatched parentheses");

            output.push_back(opStack.top());
            opStack.pop();
        }

        return output;
    }

    // ==============================
    // 4. 后缀表达式计算
    // ==============================
    double evaluatePostfix(const std::vector<Token> & postfix) {
        std::stack<double> st;

        for (const auto & token : postfix) {
            if (token.type == TokenType::Number) {
                st.push(std::stod(token.value));
            }
            else if (token.type == TokenType::Operator) {
                if (st.size() < 2)
                    throw std::runtime_error("Invalid expression");

                double b = st.top(); st.pop();
                double a = st.top(); st.pop();

                st.push(applyOperator(a, b, token.value));
            }
        }

        if (st.size() != 1)
            throw std::runtime_error("Invalid expression");

        return st.top();
    }

    double applyOperator(double a, double b, const std::string & op) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        }
        if (op == "%") {
            if (b == 0) throw std::runtime_error("Modulo by zero");
            return std::fmod(a, b);
        }
        if (op == "^" || op == "**") return std::pow(a, b);

        throw std::runtime_error("Unknown operator: " + op);
    }
};

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