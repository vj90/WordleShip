#ifndef GAMEINPUT_H
#define GAMEINPUT_H
#include <iostream>
#include <string>

#include "Guess.h"
class GameInput {
 public:
  template <typename T>
  T getUserInput(const std::string& prompt = "") {
    T input;
    std::cout << prompt << ":";
    std::cin >> input;
    return input;
  }

  GameInput() = default;
  void init(const int word_length, const int num_words);
  bool sanitizeGridCellInput(std::string& user_input) const;
  Guess convertToGuess(const std::string& grid_cell, const char letter) const;

 private:
  char min_row_{'1'};
  char max_row_{'1'};
  char min_col_{'A'};
  char max_col_{'Z'};
};
#endif  // GAMEINPUT_H