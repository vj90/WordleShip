#include <iostream>

#include "Grid.h"
#include "WordLoader.h"

void processGuess(Grid& grid) {
  std::cout << "Enter column (A-E), row (1-5), and guess" << std::endl;
  char col;
  int row;
  char guess;
  std::cout << "col: ";
  std::cin >> col;
  std::cout << "row: ";
  std::cin >> row;
  std::cout << "guess: ";
  std::cin >> guess;
  const auto res = grid.guess(col, row, guess);
  if (res.valid) {
    if (res.hit) {
      std::cout << "Hit!" << std::endl;
    } else {
      std::cout << "Miss!" << std::endl;
    }
  } else {
    std::cout << "Invalid guess" << std::endl;
  }
}

bool processInput(Grid& grid) {
  std::cout << "Press 'g' to make a guess, 'q' to exit" << std::endl;
  std::string input;
  std::cin >> input;
  if (input == "q") {
    return true;
  } else if (input == "g") {
    processGuess(grid);
  }
  return false;
}

int main() {
  std::cout << "Loading words..." << std::endl;
  WordLoader loader("wordlist.txt");
  const auto words = loader.sample_words(5);
  // print words to console
  for (const auto& word : words) {
    std::cout << word << std::endl;
  }

  Grid AI_grid(loader);
  bool exit{false};
  bool game_over{false};

  // game loop
  std::cout << "Welcome to the WordleShip!" << std::endl;
  while (!exit && !game_over) {
    AI_grid.displayGrid();
    exit = processInput(AI_grid);
  }
  AI_grid.displayGrid();
  std::cout << "Game over!" << std::endl;

  return 0;
}