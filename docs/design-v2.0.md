# Advanced Expression Calculator (C++)

A stack-based expression interpreter implemented in modern C++.

This project implements a mini expression engine supporting arithmetic,
logical operations, variables, mathematical functions, and constants.
It demonstrates core compiler/interpreter concepts such as tokenization,
operator precedence parsing (Shunting Yard Algorithm), and postfix evaluation.

---

## ✨ Features

### 1. Arithmetic Operators
- `+` Addition
- `-` Subtraction
- `*` Multiplication
- `/` Division
- `%` Modulo
- `**` Power (right-associative)

### 2. Comparison Operators
- `>`  `<`
- `>=` `<=`
- `==` `!=`

Return values:
- `1` → true
- `0` → false

### 3. Logical Operators
- `&&` Logical AND
- `||` Logical OR
- `!`  Logical NOT

### 4. Unary Operators
- Unary minus (e.g., `-5`)
- Logical NOT (`!`)

### 5. Variables


x = 10
y = 20
x + y * 2


Variables are stored in an internal symbol table.

### 6. Built-in Mathematical Functions

- `sin`
- `cos`
- `tan`
- `sqrt`
- `abs`
- `log` (base-10)
- `ln`  (natural log)
- `exp`

Example:


sin(pi / 2)
sqrt(16)


### 7. Mathematical Constants

- `pi`
- `e`

---

## 🏗 Project Structure


CalculatorProject/
│
├── main.cpp
├── include/
│ └── Calculator.h
├── src/
│ └── Calculator.cpp
├── README.md
└── DESIGN.md


---

## 🔧 Build Instructions

Using g++:


g++ main.cpp src/Calculator.cpp -Iinclude -std=c++17 -o calculator


Run:


./calculator


---

## 🧠 How It Works (High-Level)

The calculator follows a 3-stage pipeline:

1. **Tokenization**
2. **Infix to Postfix Conversion**
3. **Postfix Evaluation**

This architecture mirrors how real interpreters process expressions.

---

## 📌 Example Session


x = 5
5
y = 2
2
x ** y
25
x > y
1
sin(pi / 2)
1
!(x < y)
1


---

## 🚀 Future Improvements

- Multi-argument functions
- User-defined functions
- AST-based parser
- Type system (int / bool separation)
- Error recovery system
- GUI / Web interface

---

## 📖 Educational Value

This project demonstrates:

- Stack-based expression evaluation
- Operator precedence parsing
- Symbol table implementation
- Basic interpreter architecture
- Object-oriented design in C++