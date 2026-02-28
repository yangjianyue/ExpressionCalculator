# Design Document

## 1. Overview

This project implements a stack-based mathematical expression interpreter in C++.

The design follows classic interpreter architecture principles and separates
parsing logic from evaluation logic.

---

## 2. System Architecture

High-level processing pipeline:

User Input (string)
        ↓
Tokenizer
        ↓
Infix → Postfix Conversion (Shunting Yard)
        ↓
Postfix Evaluation (Stack Machine)
        ↓
Result (double)

---

## 3. Core Components

### 3.1 Token System

Tokens are categorized as:

- Number
- Operator
- Identifier
- LeftParen
- RightParen

This abstraction allows flexible expression parsing.

---

### 3.2 Tokenizer

Responsibility:
- Convert raw input string into structured tokens
- Recognize multi-character operators (`>=`, `<=`, `==`, `!=`, `&&`, `||`, `**`)
- Distinguish between identifiers and functions

Key techniques:
- Character classification
- Lookahead for multi-character operators

---

### 3.3 Infix to Postfix Conversion

Algorithm used:
Shunting Yard Algorithm (Dijkstra)

Responsibilities:
- Handle operator precedence
- Handle associativity (left / right)
- Handle unary operators
- Handle function calls
- Handle parentheses

Time complexity:
O(n)

---

### 3.4 Postfix Evaluation

Execution model:
Stack-based virtual machine

Rules:
- Numbers → push to stack
- Operators → pop operands, compute, push result
- Functions → pop argument(s), compute, push result

This design simplifies expression evaluation logic.

---

## 4. Operator System

Operators are defined by:

- precedence()
- isRightAssociative()

Supported categories:

Arithmetic:
+ - * / % **

Comparison:
> < >= <= == !=

Logical:
&& || !

Unary:
u- (internal representation)
!

Power operator (`**`) is right-associative.

---

## 5. Symbol Table

Variables are stored in:

std::unordered_map<std::string, double>

Assignment syntax:

x = expression

The symbol table persists for the lifetime of the Calculator instance.

---

## 6. Function Dispatching

Built-in functions are handled via:

applyFunction(functionName, argument)

Single-argument functions supported.

Design allows easy extension by adding new function branches.

---

## 7. Error Handling

Current implementation:
- Basic runtime error throwing
- Assumes valid input format

Future improvements:
- Syntax validation
- Mismatched parentheses detection
- Undefined variable detection
- Division by zero checks

---

## 8. Design Principles

- Encapsulation (Calculator class)
- Separation of interface and implementation
- Stack-based evaluation model
- Extendable operator system
- Deterministic parsing logic

---

## 9. Limitations

- Single-argument functions only
- No AST representation
- No type separation (bool/int/double unified)
- No scope system
- No user-defined functions

---

## 10. Possible Enhancements

Short-term:
- Multi-argument functions
- Error diagnostics

Mid-term:
- AST-based parser
- Type system
- Boolean type distinction

Long-term:
- Mini scripting language
- Bytecode generation
- JIT execution

---

## 11. Educational Context

This project approximates:

- Expression evaluation engine
- Simple interpreter core
- Compiler construction fundamentals

Concepts involved:

- Tokenization
- Operator precedence parsing
- Stack machine execution
- Symbol tables
- Object-oriented design

---

## 12. Conclusion

This calculator serves as a foundational interpreter model
and a stepping stone toward compiler or scripting language design.