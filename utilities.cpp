#include "automata.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Function to read a text file and print its contents using the Automata class
void lexer(std::string filepath) {
  std::ifstream file(filepath);

  // Check if the file was opened successfully
  if (!file.is_open()) {
    std::cout << "Error: Could not open file: " << filepath << std::endl;
    return;
  }

  std::string line;
  std::vector<std::string> words;

  // Process each line
  while (std::getline(file, line)) {
    // Skip empty lines
    if (line.empty() ||
        line.find_first_not_of(" \t\n\r") == std::string::npos) {
      continue;
    }

    // Extract individual words using string stream
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
      // Only add non-empty words
      if (!word.empty()) {
        words.push_back(word);
      }
    }
  }

  file.close();

  // instance of Automata class
  Automata automata;

  // Print all words and their analysis
  /*std::cout << "Words in file and their analysis:" << std::endl;
  std::cout << "--------------------------------" << std::endl;*/

  for (int i = 0; i < words.size(); ++i) {
    // analyze the word using the Automata class
    std::vector<std::pair<std::string, std::string>> analysis =
        automata.analyze(words[i]);

    // print the analysis results
    for (const auto &result : analysis) {
      std::cout << result.first << ": " << result.second << std::endl;
    }
  }
}
