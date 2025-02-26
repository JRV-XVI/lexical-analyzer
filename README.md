# Lexical Analyzer

## Summary
This project implements a lexical analyzer that processes arithmetic expressions from an input text file (`expressions.txt`). The program prints a table with every recognized token and its type in the same order as they were found.

## Types of Tokens
The arithmetic expressions should only contain the following tokens:
- **Positive integer numbers** (integer)
- **Positive real numbers** (float)
- **Operators**:
  - `=` (assignment)
  - `+` (sum)
  - `-` (subtract)
  - `*` (product)
  - `/` (division)
- **Identifiers**:
  - variable
- **Special symbols**:
  - `(` (left parenthesis)
  - `)` (right parenthesis)

## Main Function
The main function must have the following signature:
```cpp
void lexer(string filepath);