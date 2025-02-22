#include <iostream>

#include "GameParams.h"
#include "Grid.h"
#include "WordLoader.h"

bool processGuess(Grid& grid) {
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
  return res.valid;
}

struct ProcessInputStatus {
  bool exit{false};
  bool valid_guess{true};
};

ProcessInputStatus processInput(Grid& grid) {
  ProcessInputStatus status;
  std::cout << "Press 'g' to make a guess, 'q' to exit" << std::endl;
  std::string input;
  std::cin >> input;
  if (input == "q") {
    status.exit = true;
    return status;
  } else if (input == "g") {
    status.valid_guess = processGuess(grid);
  }
  return status;
}

int main() {
  std::cout << "Loading words..." << std::endl;
  WordLoader loader("wordlist.txt");

  GameParams params;
  params.setUserParams();

  Grid AI_grid(loader);
  bool exit{false};
  bool game_over{false};
  int num_guesses{0};

  // game loop
  std::cout << "Welcome to the WordleShip!" << std::endl;
  while (!exit && !game_over && num_guesses < params.max_guesses) {
    AI_grid.displayGrid();
    auto result = processInput(AI_grid);
    exit = result.exit;
    num_guesses = result.valid_guess ? num_guesses + 1 : num_guesses;
  }
  AI_grid.displayGrid();
  std::cout << "Game over!" << std::endl;

  return 0;
}