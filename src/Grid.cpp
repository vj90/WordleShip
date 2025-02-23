#include "Grid.h"

#include <assert.h>

#include <iostream>

Grid::Grid(bool show_hidden, bool highlight_hit)
    : show_hidden_(show_hidden), highlight_hit_(highlight_hit) {}

void Grid::init(WordLoader& wordloader, const int num_words) {
  assert(num_words > 0 && "Invalid number of words");
  num_words_ = num_words;
  num_hidden_ = num_words * kWordLength_;
  const auto words = wordloader.sample_words(num_words);
  word_grid_.clear();
  word_grid_.reserve(num_words);
  for (int row = 0; row < num_words; row++) {
    std::vector<GridData> row_data;
    row_data.reserve(kWordLength_);
    const auto& current_word = words.at(row);
    for (const auto& letter : current_word) {
      row_data.emplace_back(letter, true);
    }
    word_grid_.push_back(std::move(row_data));
  }
}

GuessResult Grid::guess(const Guess& player_guess) {
  assert(num_hidden_ > 0 && "Invalid grid, no more hidden letters");
  GuessResult res;
  // validate col
  const auto guess = sanitizeGuess(player_guess);
  res.valid = guess.col >= 'A' && guess.col <= 'E' && guess.row >= 1 &&
              guess.row <= num_words_;
  res.valid = res.valid && guess.guess >= 'a' && guess.guess <= 'z';
  if (res.valid) {
    // char2int
    int j = guess.col - 'A';
    int i = guess.row - 1;
    res.valid = word_grid_[i][j].is_hidden;
    if (res.valid) {
      res.hit = word_grid_[i][j].letter == guess.guess ? true : false;
      if (res.hit) {
        revealLetter(guess.guess);
      }
    }
  }
  return res;
}

void Grid::reveal(const Guess& guess) {
  const auto guess_sanitized = sanitizeGuess(guess);
  revealLetter(guess_sanitized.guess, true);
}

Guess Grid::sanitizeGuess(const Guess& player_guess) {
  const char new_col = toupper(player_guess.col, std::locale());
  const char new_guess = tolower(player_guess.guess, std::locale());
  return {new_col, player_guess.row, new_guess};
}

void Grid::revealLetter(const char letter, const bool self_reveal) {
  for (auto& row : word_grid_) {
    for (auto& grid_elem : row) {
      if (grid_elem.letter == letter) {
        if (grid_elem.is_hidden) {  // only reveal once
          grid_elem.is_hidden = false;
          grid_elem.self_revealed = self_reveal;
          num_hidden_--;
        }
      }
    }
  }
}

void Grid::displayGrid() const {
  std::cout << "  'A' 'B' 'C' 'D' 'E'\n";
  for (int i = 0; i < num_words_; i++) {
    std::cout << i + 1 << " ";
    const auto& current_row = word_grid_[i];
    for (const auto& grid_elem : current_row) {
      if (grid_elem.is_hidden && !show_hidden_) {
        std::cout << " _  ";
      } else if (!grid_elem.is_hidden && highlight_hit_) {
        const std::string highlight_symbol =
            grid_elem.self_revealed ? self_revealed_ : opponent_revealed_;
        std::cout << highlight_symbol
                  << toupper(grid_elem.letter, std::locale())
                  << highlight_symbol << " ";
      } else {
        std::cout << " " << grid_elem.letter << "  ";
      }
    }
    std::cout << "\n";
  }
}
