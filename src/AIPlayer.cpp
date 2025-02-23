#include "AIPlayer.h"

#include <ctime>
#include <iostream>

void EasyAIPlayer::init(WordLoader& wordloader) {
  // Do nothing
}

Guess EasyAIPlayer::guess(Grid& grid) {  // Find first hidden cell
  Guess guess;
  bool guessed{false};
  const auto& word_grid = grid.word_grid();
  for (int i = 0; i < word_grid.size(); ++i) {
    const auto& row = word_grid[i];
    for (int j = 0; j < row.size(); ++j) {
      if (row[j].is_hidden) {
        guess.guess = make_radom_guess();
        guess.col = 'A' + j;
        guess.row = i + 1;
        displayGuess(guess);
        return guess;
      }
    }
  }
  std::cout << "Failed to make a guess" << std::endl;
  return guess;
}

char EasyAIPlayer::make_radom_guess() {
  std::srand(std::time(nullptr));
  const int rand_num = std::rand() % 26;
  return 'a' + rand_num;
}
