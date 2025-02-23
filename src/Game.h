#ifndef GAME_H
#define GAME_H
#include <memory>
#include <string>

#include "AIPlayer.h"
#include "GameInput.h"
#include "GameParams.h"
#include "GameState.h"
#include "Grid.h"
#include "WordLoader.h"

class Talker {
 public:
  void welcome();
  void goodbye();
  void instructions();
  void guessInstructions();
  void hit();
  void miss();
  void invalidGuess();
  void AITurn();
  void invalidInput();
  void won(const std::string& who);
  std::string highlight(const std::string& text);
  std::string highlight_small(const std::string& text);
  std::string separator() { return separator_; }
  template <typename T>
  T getUserInput(const std::string& prompt = "") {
    T input;
    std::cout << prompt << ":";
    std::cin >> input;
    return input;
  }

 private:
  std::string separator_{"--------------------------"};
  std::string highlighter_{" ############# "};
  std::string highlighter_small_{"............."};
};

class Game {
 public:
  Game(const std::string& filename);
  void setUserParams();

  // getters
  GameState getState() const { return state_; }
  const GameParams& getParams() const { return params_; }

  void run();

 private:
  GameState state_;
  GameParams params_;
  WordLoader wordloader_;
  Grid user_grid_;
  Grid AI_grid_;
  Talker talker_;
  EasyAIPlayer AI_;
  GameInput ip_;

  void displayGrids();
  void processInput();
  void processAITurn();
  bool processGuess(const std::string& grid_input);
  void checkGridStatus();
};

#endif  // GAME_H