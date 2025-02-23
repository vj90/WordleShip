#include "Game.h"

#include "Guess.h"

Game::Game(const std::string& filename)
    : wordloader_(filename), user_grid_(true, true), AI_grid_(false, false) {
  // Give the user option to change params
  setUserParams();
  ip_.init(params_.kWordLength, params_.num_words);
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
    // Exit game here in case of quit command
    if (state_.exit) {
      continue;
    }
    talker_.separator();
    processAITurn();
    talker_.separator();
    // check game conditions
    checkGridStatus();
  }
  displayGrids();
  talker_.goodbye();
}

void Game::displayGrids() {
  std::cout << talker_.separator() << "\n";
  std::cout << talker_.highlight_small("AI") << "\n";
  AI_grid_.displayGrid();
  std::cout << "\n" << talker_.highlight_small(user_grid_.name()) << "\n";
  user_grid_.displayGrid();
  std::cout << talker_.separator() << std::endl;
}

void Game::processInput() {
  std::string input{"z"};
  while (input != "q" && input != "g" && !state_.exit) {
    talker_.instructions();
    input = talker_.getUserInput<std::string>();
    if (input == "q") {
      state_.exit = true;
    } else if (input == "g") {
      processGuess();
    } else {
      talker_.invalidInput();
    }
  }
}

void Game::processAITurn() {
  talker_.AITurn();
  const Guess guess = AI_.guess(user_grid_);
  const auto res = user_grid_.guess(guess);
  if (res.valid) {
    res.hit == true ? talker_.hit() : talker_.miss();
    AI_grid_.reveal(guess);
  } else {
    talker_.invalidGuess();
    std::cin.clear();
  }
}

void Game::processGuess() {
  talker_.guessInstructions();
  Guess guess;
  guess.col = talker_.getUserInput<char>("col");
  guess.row = talker_.getUserInput<int>("row");
  guess.guess = talker_.getUserInput<char>("guess");
  const auto res = AI_grid_.guess(guess);
  if (res.valid) {
    res.hit == true ? talker_.hit() : talker_.miss();
    state_.num_guesses++;
    user_grid_.reveal(guess);
  } else {
    talker_.invalidGuess();
  }
}

void Game::checkGridStatus() {
  if (user_grid_.revealed() || AI_grid_.revealed()) {
    if (user_grid_.revealed() && AI_grid_.revealed()) {
      talker_.won("Both");

    } else if (user_grid_.revealed()) {
      talker_.won("AI");
    } else {
      talker_.won("User");
    }
    state_.game_over = true;
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
  std::cout << "\n\t\t\t\t\t" << highlight_small("Hit!") << std::endl;
}
void Talker::miss() {
  std::cout << "\n\t\t\t\t\t" << highlight_small("Miss!") << std::endl;
}
void Talker::invalidGuess() {
  std::cout << "Invalid guess. Try again." << std::endl;
}

void Talker::AITurn() {
  std::cout << highlight_small("AI's turn") << std::endl;
}

void Talker::invalidInput() {
  std::cout << "Invalid input. Try again." << std::endl;
}

void Talker::won(const std::string& who) {
  std::cout << highlight("Congratulations, " + who + " won!") << std::endl;
}