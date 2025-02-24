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
  const auto [j, i] = get_grid_idx(player_guess);
  // validate guess
  res.valid = validateGuess(i, j, player_guess.guess);

  if (res.valid) {
    res.hit = word_grid_[i][j].letter == player_guess.guess ? true : false;
    if (res.hit) {
      revealLetter(player_guess.guess);
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
  // Invalidate letter for entire grid
  const int char_idx = letter - grid_alphabet_start;
  grid_invalid_letters_.set(char_idx);
}

bool Grid::validateGuess(const int cell_row_idx, const int cell_col_idx,
                         char player_letter) {
  auto& cell = word_grid_[cell_row_idx][cell_col_idx];
  bool valid = {false};
  // cell within grids
  valid = (cell_row_idx < num_words_) && (cell_col_idx < kWordLength_);
#ifdef DEBUG
  if (!valid) {
    std::cout << "\nGrid cell out of bounds\n";
  }
#endif
  // cell is hidden
  valid = valid && cell.is_hidden;
#ifdef DEBUG
  if (!valid) {
    std::cout << "\nGrid cell already revealed\n";
  }
#endif
  // guessed letter is valid
  const int char_idx = player_letter - grid_alphabet_start;
  valid = valid && !(cell.cell_invalid_letters[char_idx] ||
                     grid_invalid_letters_[char_idx]);
#ifdef DEBUG
  if (!valid) {
    std::cout << "\nChar idx = " << char_idx << "\n";
    std::cout << "grid_invalid_letters_ = " << grid_invalid_letters_ << "\n";
    std::cout << "cell.cell_invalid_letters = " << cell.cell_invalid_letters
              << "\n";
    std::cout << "\nGuessed letter already guessed\n";
  }
#endif
  // if valid, then invalidate this letter for this cell
  if (valid) {
    cell.cell_invalid_letters.set(char_idx);
  }
  return valid;
}

std::pair<int /*col*/, int /*row*/> Grid::get_grid_idx(
    const Guess& guess) const {
  int j = guess.col - col_alphabet_start;
  int i = guess.row - 1;
  return {j, i};
}

void Grid::displayKeyboard() const { keyboard_.display(grid_invalid_letters_); }
void Grid::displayCellKeyboard(const Guess& guess) const {
  const auto [col, row] = get_grid_idx(guess);
  const auto& cell_invalid_letters = word_grid_[row][col].cell_invalid_letters;
  keyboard_.display(grid_invalid_letters_, cell_invalid_letters);
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
