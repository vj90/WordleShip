#include "Grid.h"

#include <assert.h>

#include <iostream>

Grid::Grid(WordLoader& wordloader, bool show_hidden, bool highlight_hit,
           int num_words)
    : show_hidden_(show_hidden),
      highlight_hit_(highlight_hit),
      num_words_(num_words),
      num_hidden_(num_words * kWordLength_) {
  const auto words = wordloader.sample_words(num_words);
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

GuessResult Grid::guess(const char col_in, const int row_in, const char guess) {
  assert(num_hidden_ > 0 && "Invalid grid, no more hidden letters");
  GuessResult res;
  // validate col
  auto [col, row] = sanitizeGuess(col_in, row_in);
  res.valid = col >= 'A' && col <= 'E' && row >= 1 && row <= num_words_;
  if (res.valid) {
    // char2int
    int j = col - 'A';
    int i = row - 1;
    res.valid = word_grid_[i][j].is_hidden;
    if (res.valid) {
      res.hit = word_grid_[i][j].letter == guess ? true : false;
      if (res.hit) {
        for (auto& row : word_grid_) {
          for (auto& grid_elem : row) {
            if (grid_elem.letter == guess) {
              grid_elem.is_hidden = false;
              num_hidden_--;
            }
          }
        }
      }
    }
  }
  return res;
}

std::pair<char, int> Grid::sanitizeGuess(const char col, const int row) {
  const char new_col = toupper(col, std::locale());
  return std::make_pair(new_col, row);
}

void Grid::displayGrid() const {
  std::cout << "  A B C D E\n";
  for (int i = 0; i < num_words_; i++) {
    std::cout << i + 1 << " ";
    const auto& current_row = word_grid_[i];
    for (const auto& grid_elem : current_row) {
      if (grid_elem.is_hidden && !show_hidden_) {
        std::cout << "_ ";
      } else if (!grid_elem.is_hidden && highlight_hit_) {
        std::cout << toupper(grid_elem.letter, std::locale()) << " ";
      } else {
        std::cout << grid_elem.letter << " ";
      }
    }
    std::cout << "\n";
  }
}
