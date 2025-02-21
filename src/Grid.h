#ifndef GRID_H
#define GRID_H
#include <array>
#include <vector>

#include "WordLoader.h"

struct GridData {
  GridData(char letter, bool is_hidden)
      : letter(letter), is_hidden(is_hidden) {}
  char letter{'_'};
  bool is_hidden{true};
};

struct GuessResult {
  bool valid{false};
  bool hit{false};
};

class Grid {
 public:
  Grid(WordLoader& wordloader, bool show_hidden = false,
       bool highlight_hit = false, int num_words = 5);
  void displayGrid() const;
  GuessResult guess(const char col_in, const int row_in, const char guess);
  bool revealed() const { return num_hidden_ == 0; }

  // setters and getters
  void set_show_hidden(bool show_hidden) { show_hidden_ = show_hidden; }
  bool get_show_hidden() const { return show_hidden_; }
  void set_highlight_hit(bool highlight_hit) { highlight_hit_ = highlight_hit; }
  bool get_highlight_hit() const { return highlight_hit_; }

 private:
  static constexpr int kWordLength_{5};
  int num_words_;
  std::vector<std::vector<GridData>> word_grid_;
  bool show_hidden_{false};
  bool highlight_hit_{false};
  int num_hidden_{-1};

  std::pair<char, int> sanitizeGuess(const char col, const int row);
};
#endif