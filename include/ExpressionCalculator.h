#pragma once
#include <string>
#include <vector>

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
    double evaluate(const std::string& expr);

private:
    std::vector<Token> tokenize(const std::string& expr);
    void handleUnaryOperators(std::vector<Token>& tokens);
    int precedence(const std::string& op);
    bool isRightAssociative(const std::string& op);
    std::vector<Token> infixToPostfix(const std::vector<Token>& tokens);
    double evaluatePostfix(const std::vector<Token>& postfix);
    double applyOperator(double a, double b, const std::string& op);
};