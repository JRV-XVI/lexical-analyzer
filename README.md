# Lexical Analyzer
## How to run the program
You must compile `main.cpp` and `utilities.cpp` to be able to run the program.
The commands run compile it and run it at best performence: 

`g++ -O3 main.cpp utilities.cpp -o main`

`./main`

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
You can code any auxiliary function you want but the main function must have the following signature (could change depending on the programming language):

void lexer(string filepath):

where filepath is the path to the file that contains the expressions, for example, expressions.txt.
