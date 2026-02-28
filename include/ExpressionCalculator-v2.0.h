#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <unordered_map>

class Calculator {
public:
    double evaluate(const std::string& expr);

private:
    enum class TokenType {
        Number,
        Operator,
        Identifier,
        LeftParen,
        RightParen
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    std::unordered_map<std::string, double> variables;

    std::vector<Token> tokenize(const std::string& expr);
    std::vector<Token> infixToPostfix(const std::vector<Token>& tokens);
    double evaluatePostfix(const std::vector<Token>& postfix);

    int precedence(const std::string& op);
    bool isRightAssociative(const std::string& op);

    double applyOperator(const std::string& op, double a, double b);
    double applyFunction(const std::string& func, double arg);
};

#endif