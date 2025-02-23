#include "GameInput.h"

void GameInput::init(const int word_length, const int num_words) {
  max_row_ = '0' + num_words;
  min_col_ = 'A';
  max_col_ = 'A' + word_length - 1;
}

bool GameInput::sanitizeGridCellInput(std::string& user_input) const {
  if (user_input.size() != 2) {
    return false;
  }
  const auto& row_char = user_input[1];
  auto& col_char = user_input[0];
  col_char = std::toupper(col_char);
  if (row_char < min_row_ || row_char > max_row_) {
    return false;
  }
  if (col_char < min_col_ || col_char > max_col_) {
    return false;
  }
  return true;
}

Guess GameInput::convertToGuess(const std::string& grid_cell,
                                const char letter) const {
  return Guess{grid_cell[0], grid_cell[1] - '0', letter};
}
