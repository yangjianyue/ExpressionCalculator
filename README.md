# Expression Calculator

A command-line expression calculator implemented in C++.  

This project supports evaluation of infix mathematical expressions with proper operator precedence and parentheses handling.

---


\## 📌 Project Overview

Expression Calculator is a C++ console application that parses and evaluates mathematical expressions entered by the user.

It demonstrates:

\- Tokenization (Lexical Analysis)

\- Infix to Postfix conversion (Shunting-yard Algorithm)

\- Stack-based Postfix Evaluation

\- Exception handling

\- Object-Oriented Programming design

---

\## ✨ Features

\- Supports operators:

&nbsp; - Addition: `+`

&nbsp; - Subtraction: `-`

&nbsp; - Multiplication: `\*`

&nbsp; - Division: `/`

&nbsp; - Modulo: `%`

&nbsp; - Power: `^` and `\*\*`

\- Supports:

&nbsp; - Parentheses `()`

&nbsp; - Floating point numbers

&nbsp; - Unary `+` and `-`

\- Error handling:

&nbsp; - Division by zero

&nbsp; - Modulo by zero

&nbsp; - Mismatched parentheses

&nbsp; - Invalid expressions


---


\## 🧠 Core Algorithm


The calculator works in three major stages:


\### 1️⃣ Tokenization

The input string is parsed into tokens:

\- Numbers

\- Operators

\- Parentheses


\### 2️⃣ Infix → Postfix Conversion

Uses the \*\*Shunting-yard algorithm\*\* to convert infix expressions into postfix notation based on operator precedence and associativity.


\### 3️⃣ Postfix Evaluation

A stack-based algorithm evaluates the postfix expression to produce the final result.


---

\## 🗂 Project Structure

ExpressionCalculator/

│

├── src/

│ └── main.cpp

│

├── README.md

└── .gitignore

---

\## ⚙️ Requirements

\- C++11 or later

\- g++ compiler (or compatible C++ compiler)

---

\## 🛠 Build Instructions

Navigate to the project directory and run:

g++ src/main.cpp -std=c++11 -o calculator

---

\## ▶️ Run

./calculator

Example:

2 + 3 \* 4

14

(2 + 3) \* 4

20

2 ^ 3

8

To exit:

exit

---

\## 🚨 Error Handling

The program throws runtime exceptions for:

\- Division by zero

\- Modulo by zero

\- Invalid expressions

\- Mismatched parentheses

All exceptions are caught and displayed as user-friendly error messages.

---

\## 🏗 Design Principles

\- Object-Oriented Design

\- Separation of logic into modular functions

\- Clean exception handling

\- Standard Library usage (STL containers and algorithms)

---

\## 📚 Concepts Demonstrated

\- `std::vector`

\- `std::stack`

\- `std::string`

\- `std::stod`

\- Exception handling with `std::runtime\_error`

\- Operator precedence handling

\- Right-associative operator support

--

\## 🔮 Possible Future Improvements

\- Support for functions like `sin()`, `cos()`, `log()`

\- Support for variables

\- GUI interface

\- Unit tests

\- CMake build system

