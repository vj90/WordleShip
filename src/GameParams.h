#ifndef GAMEPARAMS_H
#define GAMEPARAMS_H
#include <iostream>
#include <ostream>
struct GameParams {
  int num_words{5};
  int max_guesses{50};

  void setUserParams() {
    std::cout << "Current parameters:\n" << *this;
    char input{'z'};
    while (input != 'y' && input != 'n') {
      std::cout << "Enter new parameters? y/n:";
      std::cin >> input;
    }
    if (input == 'y') {
      char param_num{'z'};
      while (param_num != 'q') {
        std::cout << "Enter parameter number to change. Press q to exit: ";
        std::cin >> param_num;
        switch (param_num) {
          case '1': {
            std::cout << "Enter new number of words: ";
            int input_num_words;
            std::cin >> input_num_words;
            if (input_num_words < 1 || input_num_words > 10) {
              std::cout << "Invalid number of words" << std::endl;
            } else {
              num_words = input_num_words;
            }
            break;
          }
          case '2': {
            std::cout << "Enter new max number of guesses: ";
            int input_max_guesses;
            std::cin >> input_max_guesses;
            if (input_max_guesses < 1 || input_max_guesses > 1000) {
              std::cout << "Invalid number of guesses" << std::endl;
            } else {
              max_guesses = input_max_guesses;
            }
            break;
          }
          case 'q':
            break;
          default:
            std::cout << "Invalid parameter number\n" << *this;
        }
      }
    }
  }
  friend std::ostream& operator<<(std::ostream& os, const GameParams& params) {
    os << "1. Number of words      : " << params.num_words << "\n";
    os << "2. Max number of guesses: " << params.max_guesses << "\n";
    return os;
  }
};

#endif  // GAMEPARAMS_H