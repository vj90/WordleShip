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

GuessResult Grid::guess(const char col_in, const int row_in,
                        const char guess_in) {
  assert(num_hidden_ > 0 && "Invalid grid, no more hidden letters");
  GuessResult res;
  // validate col
  auto [col, row, guess] = sanitizeGuess(col_in, row_in, guess_in);
  res.valid = col >= 'A' && col <= 'E' && row >= 1 && row <= num_words_;
  res.valid = res.valid && guess >= 'a' && guess <= 'z';
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

std::tuple<char, int, char> Grid::sanitizeGuess(const char col, const int row,
                                                const char guess) {
  const char new_col = toupper(col, std::locale());
  const char new_guess = tolower(guess, std::locale());
  return std::make_tuple(new_col, row, new_guess);
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
