#include "Game.h"

Game::Game(const std::string& filename)
    : wordloader_(filename), user_grid_(true, true), AI_grid_(false, false) {
  // Give the user option to change params
  setUserParams();
  user_grid_.init(wordloader_, params_.num_words);
  user_grid_.set_name("User");
  AI_grid_.init(wordloader_, params_.num_words);
}

void Game::setUserParams() { params_.setUserParams(); }

void Game::run() {
  state_.reset();
  talker_.welcome();
  while (state_.gameOn(params_.max_guesses)) {
    displayGrids();
    processInput();
    talker_.separator();
    // check game conditions
  }
  displayGrids();
  talker_.goodbye();
}

void Game::displayGrids() {
  std::cout << talker_.separator() << "\n";
  std::cout << talker_.highlight_small("AI") << "\n";
  AI_grid_.displayGrid();
  std::cout << talker_.highlight_small(user_grid_.name()) << "\n";
  user_grid_.displayGrid();
  std::cout << talker_.separator() << std::endl;
}

void Game::processInput() {
  talker_.instructions();
  const auto input = talker_.getUserInput<std::string>();
  if (input == "q") {
    state_.exit = true;
  } else if (input == "g") {
    processGuess();
  }
}

void Game::processGuess() {
  talker_.guessInstructions();
  const auto col = talker_.getUserInput<char>("col");
  const auto row = talker_.getUserInput<int>("row");
  const auto guess = talker_.getUserInput<char>("guess");
  const auto res = AI_grid_.guess(col, row, guess);
  if (res.valid) {
    res.hit == true ? talker_.hit() : talker_.miss();
    state_.num_guesses++;
  } else {
    talker_.invalidGuess();
  }
}

// ################################################################################

void Talker::welcome() {
  std::cout << highlight("Welcome to WordleShip!") << std::endl;
}
void Talker::goodbye() { std::cout << highlight("Game over!") << std::endl; }

std::string Talker::highlight(const std::string& text) {
  return highlighter_ + text + highlighter_;
}
std::string Talker::highlight_small(const std::string& text) {
  return highlighter_small_ + text + highlighter_small_;
}

void Talker::instructions() {
  std::cout << "Press 'g' to make a guess, 'q' to exit" << std::endl;
}

void Talker::guessInstructions() {
  std::cout << "Enter column (A-E), row (1-5), and guess" << std::endl;
}

void Talker::hit() {
  std::cout << "\n" << highlight_small("Hit!") << std::endl;
}
void Talker::miss() {
  std::cout << "\n" << highlight_small("Miss!") << std::endl;
}
void Talker::invalidGuess() {
  std::cout << "Invalid guess. Try again." << std::endl;
}