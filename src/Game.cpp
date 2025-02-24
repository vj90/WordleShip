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
  std::cout << "\n" << talker_.highlight_small(user_grid_.name()) << "\n";
  user_grid_.displayGrid();
  std::cout << talker_.highlight_small("AI") << "\n";
  AI_grid_.displayGrid();
  std::cout << talker_.separator() << std::endl;
}

void Game::processInput() {
  bool stay_in_current_turn{true};
  while (!state_.exit && stay_in_current_turn) {
    talker_.instructions();
    std::string input = talker_.getUserInput<std::string>();
    const bool grid_input_valid = ip_.sanitizeGridCellInput(input);
    if (grid_input_valid) {
      // Take further inputs
      const bool valid_guess = processGuess(input);
      stay_in_current_turn = valid_guess ? false : true;
    } else if (input == "q") {
      state_.exit = true;
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

bool Game::processGuess(const std::string& grid_input) {
  talker_.guessInstructions();
  Guess guess = ip_.convertToGuess(grid_input,  //
                                   talker_.getUserInput<char>("guess"));

  const auto res = AI_grid_.guess(guess);
  if (res.valid) {
    res.hit == true ? talker_.hit() : talker_.miss();
    state_.num_guesses++;
    user_grid_.reveal(guess);
  } else {
    talker_.invalidGuess();
  }
  return res.valid;
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
  std::cout << "Enter grid position to guess (<A-E><1-5>), 'q' to exit"
            << std::endl;
}

void Talker::guessInstructions() {
  std::cout << "Enter a letter <a-z>" << std::endl;
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
  std::cout << "Invalid input. Examples of inputs :\"D3\", \"e4\" Try again."
            << std::endl;
}

void Talker::won(const std::string& who) {
  std::cout << highlight("Congratulations, " + who + " won!") << std::endl;
}