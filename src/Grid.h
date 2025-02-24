#ifndef GRID_H
#define GRID_H
#include <array>
#include <bitset>
#include <tuple>
#include <vector>

#include "Guess.h"
#include "Keyboard.h"
#include "WordLoader.h"

struct GridData {
  GridData(char letter, bool is_hidden)
      : letter(letter), is_hidden(is_hidden) {}
  char letter{'_'};
  bool is_hidden{true};
  bool self_revealed{false};
  std::bitset<26> cell_invalid_letters;
  void make_all_letters_invalid() { cell_invalid_letters.set(); }
};

class Grid {
 public:
  Grid(bool show_hidden = false, bool highlight_hit = false);
  void init(WordLoader& wordloader, const int num_words);

  void displayGrid() const;
  GuessResult guess(const Guess& player_guess);
  bool revealed() const { return num_hidden_ == 0; }
  void reveal(const Guess& guess);
  void displayKeyboard() const;
  void displayCellKeyboard(const Guess& guess) const;

  // setters and getters
  void set_show_hidden(bool show_hidden) { show_hidden_ = show_hidden; }
  bool get_show_hidden() const { return show_hidden_; }
  void set_highlight_hit(bool highlight_hit) { highlight_hit_ = highlight_hit; }
  bool get_highlight_hit() const { return highlight_hit_; }
  void set_name(const std::string& name) { name_ = name; }
  const std::string& name() const { return name_; }
  const std::vector<std::vector<GridData>>& word_grid() const {
    return word_grid_;
  }
  const std::bitset<26>& gridInvalidLetters() const {
    return grid_invalid_letters_;
  }
  // public members;
  static constexpr char grid_alphabet_start{'a'};  // letters in grid are small
  static constexpr char col_alphabet_start{'A'};   // column letters are BIG

 private:
  static constexpr int kWordLength_{5};

  int num_words_{-1};
  std::vector<std::vector<GridData>> word_grid_;
  bool show_hidden_{false};
  bool highlight_hit_{false};
  int num_hidden_{-1};
  std::string name_{"AI"};
  const std::string self_revealed_{"'"};
  const std::string opponent_revealed_{"*"};
  std::bitset<26> grid_invalid_letters_;
  Keyboard keyboard_;

  Guess sanitizeGuess(const Guess& player_guess);
  void revealLetter(const char letter, const bool self_reveal = false);
  bool validateGuess(const int cell_row_idx, const int cell_col_idx,
                     char player_letter);
  std::pair<int /*col*/, int /*row*/> get_grid_idx(const Guess& guess) const;
};

#endif