#include <iostream>

#include "Grid.h"

void displayGrid() {
  std::cout << "  A B C D E" << std::endl;
  std::cout << "1 _ _ _ _ _" << std::endl;
  std::cout << "2 _ _ _ _ _" << std::endl;
  std::cout << "3 _ _ _ _ _" << std::endl;
  std::cout << "4 _ _ _ _ _" << std::endl;
  std::cout << "5 _ _ _ _ _" << std::endl;
}

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

int main() {
  // start game
  std::cout << "Welcome to the WordleShip!" << std::endl;
  Grid AI_grid;
  bool exit{false};
  bool game_over{false};
  while (!exit && !game_over) {
    AI_grid.displayGrid();
    std::cout << "Press 'g' to make a guess, 'q' to exit" << std::endl;
    std::string input;
    std::cin >> input;
    if (input == "q") {
      exit = true;
    } else if (input == "g") {
      processGuess(AI_grid);
      game_over = AI_grid.revealed();
    }
  }
  AI_grid.displayGrid();
  std::cout << "Game over!" << std::endl;
  return 0;
}