#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include <cctype>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen,
    Identifier
};

struct Token {
    TokenType type;
    std::string value;
};

class ExpressionCalculator {
private:
    std::unordered_map<std::string, double> variables;//键值对容器

public:
    double evaluate(const std::string& expr) {
        auto tokens = tokenize(expr);

        // 处理赋值
        if (tokens.size() >= 3 &&
            tokens[0].type == TokenType::Identifier &&
            tokens[1].type == TokenType::Operator &&
            tokens[1].value == "=") {

            std::string varName = tokens[0].value;
            tokens.erase(tokens.begin(), tokens.begin() + 2);

            auto postfix = infixToPostfix(tokens);
            double val = evaluatePostfix(postfix);
            variables[varName] = val;
            return val;
        }

        auto postfix = infixToPostfix(tokens);
        return evaluatePostfix(postfix);
    }

private:
    std::vector<Token> tokenize(const std::string& expr) {
        std::vector<Token> tokens;

        for (size_t i = 0; i < expr.size();) {

            if (isspace(expr[i])) {
                i++;
            }
            else if (isdigit(expr[i]) || expr[i] == '.') {
                std::string num;
                while (i < expr.size() &&
                    (isdigit(expr[i]) || expr[i] == '.')) {
                    num += expr[i++];
                }
                tokens.push_back({ TokenType::Number, num });
            }
            else if (isalpha(expr[i])) {
                std::string name;
                while (i < expr.size() &&
                    (isalnum(expr[i]) || expr[i] == '_')) {
                    name += expr[i++];
                }
                tokens.push_back({ TokenType::Identifier, name });
            }
            else {
                // 处理双字符运算符
                if (i + 1 < expr.size()) {
                    std::string two = expr.substr(i, 2);
                    if (two == ">=" || two == "<=" ||
                        two == "==" || two == "!=" ||
                        two == "&&" || two == "||" ||
                        two == "**") {

                        tokens.push_back({ TokenType::Operator, two });
                        i += 2;
                        continue;//防止后续再进行单字符运算符的判定
                    }
                }

                if (expr[i] == '(')
                    tokens.push_back({ TokenType::LeftParen, "(" });
                else if (expr[i] == ')')
                    tokens.push_back({ TokenType::RightParen, ")" });
                else
                    tokens.push_back({ TokenType::Operator,
                                      std::string(1, expr[i]) });
                i++;
            }
        }

        return tokens;
    }

    int precedence(const std::string& op) {
        if (op == "!") return 7;
        if (op == "**") return 6;
        if (op == "*" || op == "/") return 5;
        if (op == "+" || op == "-") return 4;
        if (op == ">" || op == "<" ||
            op == ">=" || op == "<=") return 3;
        if (op == "==" || op == "!=") return 2;
        if (op == "&&") return 1;
        if (op == "||") return 0;
        return -1;
    }

    bool isRightAssociative(const std::string& op) {
        return op == "!" || op == "**";
    }

    std::vector<Token> infixToPostfix(const std::vector<Token>& tokens) {
        std::vector<Token> output;
        std::stack<Token> ops;

        for (size_t i = 0; i < tokens.size(); ++i) {
            const Token& t = tokens[i];

            if (t.type == TokenType::Number)
                output.push_back(t);

            else if (t.type == TokenType::Identifier) {
                if (i + 1 < tokens.size() &&
                    tokens[i + 1].type == TokenType::LeftParen) {
                    ops.push(t); // 函数
                }
                else {
                    output.push_back(t);
                }
            }

            else if (t.type == TokenType::Operator) {

                std::string op = t.value;

                // 一元负号
                if (op == "-" &&
                    (i == 0 ||
                        tokens[i - 1].type == TokenType::Operator ||
                        tokens[i - 1].type == TokenType::LeftParen)) {
                    op = "u-";//单目负号
                }

                while (!ops.empty() &&
                    ops.top().type == TokenType::Operator &&
                    ((precedence(ops.top().value) > precedence(op)) ||
                        (precedence(ops.top().value) == precedence(op) &&
                            !isRightAssociative(op)))) {
                    output.push_back(ops.top());
                    ops.pop();
                }

                ops.push({ TokenType::Operator, op });
            }

            else if (t.type == TokenType::LeftParen) {
                ops.push(t);
            }

            else if (t.type == TokenType::RightParen) {
                while (!ops.empty() &&
                    ops.top().type != TokenType::LeftParen) {
                    output.push_back(ops.top());
                    ops.pop();
                }

                if (!ops.empty())
                    ops.pop();//去除左括号

                if (!ops.empty() &&
                    ops.top().type == TokenType::Identifier) {
                    output.push_back(ops.top());
                    ops.pop();//针对函数，左括号左边是函数名的情况处理
                }
            }
        }

        while (!ops.empty()) {
            output.push_back(ops.top());
            ops.pop();
        }

        return output;
    }

    double applyFunction(const std::string& name, double x) {
        if (name == "sin") return sin(x);
        if (name == "cos") return cos(x);
        if (name == "tan") return tan(x);
        if (name == "sqrt") return sqrt(x);
        if (name == "abs") return fabs(x);
        if (name == "log") return log10(x);
        if (name == "ln") return log(x);
        if (name == "exp") return exp(x);

        throw std::runtime_error("Unknown function: " + name);
    }//应用具体数学函数

    double applyOperator(const std::string& op,
        double a, double b) {

        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0)
                throw std::runtime_error("Divide by zero");
            return a / b;
        }
        if (op == "**") return pow(a, b);

        if (op == ">") return a > b;
        if (op == "<") return a < b;
        if (op == ">=") return a >= b;
        if (op == "<=") return a <= b;
        if (op == "==") return a == b;
        if (op == "!=") return a != b;

        if (op == "&&") return (a != 0 && b != 0);
        if (op == "||") return (a != 0 || b != 0);

        throw std::runtime_error("Unknown operator: " + op);
    }//应用基础运算规则，逻辑运算符与比较运算符

    double evaluatePostfix(const std::vector<Token>& postfix) {
        std::stack<double> st;

        for (const auto& t : postfix) {

            if (t.type == TokenType::Number)
                st.push(std::stod(t.value));

            else if (t.type == TokenType::Identifier) {
                if (variables.count(t.value))
                    st.push(variables[t.value]);
                else if (t.value == "pi")
                    st.push(M_PI);
                else if (t.value == "e")
                    st.push(M_E);
                else {
                    double arg = st.top(); st.pop();
                    st.push(applyFunction(t.value, arg));
                }
            }

            else if (t.type == TokenType::Operator) {

                if (t.value == "u-") {
                    double a = st.top(); st.pop();
                    st.push(-a);
                    continue;
                }

                if (t.value == "!") {
                    double a = st.top(); st.pop();
                    st.push(!(a != 0));
                    continue;
                }

                double b = st.top(); st.pop();
                double a = st.top(); st.pop();
                st.push(applyOperator(t.value, a, b));
            }
        }

        return st.top();
    }
};

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