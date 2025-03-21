# Arithmetic Expression Parser and Calculator

![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-brightgreen)

A command-line calculator that parses and evaluates mathematical expressions with support for advanced operations and error handling.

## Features
- Basic arithmetic operations (`+`, `-`, `*`, `/`)
- Power operator (`^`)
- Unary minus support
- Parentheses handling
- Error detection for:
  - Invalid characters
  - Mismatched brackets
  - Division by zero
  - Empty input
- Reverse Polish Notation (postfix) conversion

## Dependencies
- C++11 compatible compiler
- CMake (>= 3.20)

## Project Structure
```
.
├── CMakeLists.txt      - Build configuration
├── main.cpp            - Main entry point and I/O handling
└── expressions.hpp     - Core parsing and calculation logic
    ├── Lexeme         - Token representation
    ├── parse()        - Input validation and tokenization
    ├── postfixForm()  - Shunting-yard algorithm
    └── countUp()      - Postfix expression evaluation
```

## Implementation Details
- Lexer: Converts input string to tokens with type and priority
- Parser: Validates token sequence and detects errors
- Shunting-yard Algorithm: Converts infix to postfix notation
- Stack Machine: Evaluates postfix expressions
- Supports operator precedence:
  - Parentheses
  - Exponentiation (^)
  - Unary minus
  - Multiplication/Division
  - Addition/Subtraction

## Error Handling
Examples of caught errors:
```
input expression: 2++3
incorrect input: error with parsing

input expression: 2/(5-5)
incorrect input: can't divide to 0

input expression: 2+(3*4
incorrect input: invalid brackets
```
