#include "AIPlayer.h"

#include <ctime>
#include <iostream>

void EasyAIPlayer::init(WordLoader& wordloader) {
  // Do nothing
}

Guess EasyAIPlayer::guess(Grid& grid) {  // Find first hidden cell
  Guess guess;

  const auto& word_grid = grid.word_grid();
  for (int i = 0; i < word_grid.size(); ++i) {
    const auto& row = word_grid[i];
    for (int j = 0; j < row.size(); ++j) {
      if (row[j].is_hidden) {
        bool guessed{false};
        int char_idx = -1;
        while (!guessed) {
          char_idx = make_radom_guess();
          guessed = (!row[j].cell_invalid_letters[char_idx]) &&
                    !grid.gridInvalidLetters()[char_idx];
          guess.guess = make_radom_guess();
        }
        guess.guess = grid.grid_alphabet_start + char_idx;
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

int EasyAIPlayer::make_radom_guess() {
  std::srand(std::time(nullptr));
  const int rand_num = std::rand() % 26;
  return rand_num;
}
