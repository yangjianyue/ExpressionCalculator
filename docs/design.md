# Design Document

## 1. Project Overview

Expression Calculator is a command-line mathematical expression evaluator written in C++.  
The system parses infix expressions entered by users and computes the result using a structured multi-stage processing pipeline.

The primary design goals are:

- Clear modular structure
- Correct operator precedence handling
- Support for parentheses and unary operators
- Robust error handling
- Clean and maintainable code design

---

## 2. System Architecture

The system follows a linear processing pipeline:


Input String
↓
Tokenizer
↓
Infix to Postfix Converter (Shunting-yard Algorithm)
↓
Postfix Evaluator
↓
Result Output


Each stage is separated into independent functions inside the `ExpressionCalculator` class to ensure modularity and maintainability.

---

## 3. Core Components

### 3.1 ExpressionCalculator Class

The entire calculation logic is encapsulated in a single class:


class ExpressionCalculator


Responsibilities:

- Orchestrate evaluation process
- Manage tokenization
- Convert infix to postfix
- Evaluate postfix expression
- Handle runtime errors

Public Interface:


double evaluate(const std::string& expr);


This method serves as the entry point for expression evaluation.

---

## 4. Algorithm Design

### 4.1 Tokenization (Lexical Analysis)

The tokenizer scans the input string character by character and produces a sequence of tokens:

Token types:

- Number
- Operator
- Left Parenthesis
- Right Parenthesis

Special Handling:

- Floating-point numbers
- Multi-character operator (`**`)
- Unary operators (`+` and `-`)

Unary operators are handled by inserting a `0` before them when necessary.

Example:


-5 + 3


Converted internally to:


0 - 5 + 3


This simplifies later evaluation logic.

---

### 4.2 Infix to Postfix Conversion

The project uses the **Shunting-yard algorithm**.

Key rules:

- Numbers → directly pushed to output
- Operators → managed by precedence and associativity
- Left parenthesis → pushed to stack
- Right parenthesis → pop until matching left parenthesis

Operator precedence:

| Operator | Precedence |
|----------|------------|
| + -      | 1          |
| * / %    | 2          |
| ^ **     | 3          |

Associativity:

- `^` and `**` are right-associative
- Others are left-associative

This ensures correct mathematical evaluation order.

---

### 4.3 Postfix Evaluation

The postfix expression is evaluated using a stack-based algorithm.

Algorithm:

1. If token is number → push to stack
2. If token is operator:
   - Pop two operands
   - Apply operation
   - Push result back

Final result remains as the single value in the stack.

Time Complexity:  
O(n), where n is the number of tokens.

---

## 5. Error Handling Strategy

The system uses `std::runtime_error` for runtime error detection.

Handled errors include:

- Division by zero
- Modulo by zero
- Mismatched parentheses
- Invalid expression format
- Unknown operators

All exceptions are caught in `main()` and displayed as user-friendly messages.

---

## 6. Design Decisions

### 6.1 Why Postfix Instead of Direct Evaluation?

Postfix evaluation:

- Eliminates parentheses complexity
- Simplifies precedence handling
- Enables clean stack-based computation
- Improves maintainability

### 6.2 Why Use STL Containers?

- `std::vector` → dynamic token storage
- `std::stack` → operator and evaluation stack
- `std::string` → safe string manipulation

Using STL improves reliability and reduces manual memory management.

---

## 7. Complexity Analysis

| Stage | Time Complexity |
|-------|------------------|
| Tokenization | O(n) |
| Infix → Postfix | O(n) |
| Postfix Evaluation | O(n) |

Overall Complexity:

O(n)

Space Complexity:

O(n)

---

## 8. Limitations

- No support for variables
- No support for functions like sin(), cos()
- No implicit multiplication (e.g., 2(3+4))
- No scientific notation parsing

---

## 9. Possible Improvements

Future enhancements may include:

- Support for mathematical functions
- Support for variables
- Expression history
- Unit testing module
- CMake build system
- GUI interface
- Extensible operator registration

---

## 10. Conclusion

This project demonstrates:

- Object-Oriented Design
- Stack-based expression evaluation
- Implementation of classical parsing algorithms
- Structured error handling
- Clean modular code architecture

The design prioritizes correctness, clarity, and extensibility.