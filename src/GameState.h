#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <iostream>
struct GameState {
  int num_guesses{0};
  bool exit{false};
  bool game_over{false};
  friend std::ostream& operator<<(std::ostream& os, const GameState& state) {
    os << "Guesses: " << state.num_guesses << "\nGame over: " << state.game_over
       << "\nExit: " << state.exit << std::endl;
    return os;
  }
  void reset() {
    num_guesses = 0;
    game_over = false;
    exit = false;
  }

  bool gameOn(const int max_guesses) {
    return !exit && !game_over && num_guesses < max_guesses;
  }
};
#endif  // GAMESTATE_H
