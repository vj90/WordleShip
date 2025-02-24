#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <iostream>

#include "Grid.h"
#include "Guess.h"
#include "WordLoader.h"

class AIPlayer {
 public:
  AIPlayer() = default;
  virtual void init(WordLoader& wordloader) = 0;
  virtual Guess guess(Grid& grid) = 0;
  void displayGuess(const Guess& guess) {
    std::cout << "AI guessed: " << guess.guess << " at " << guess.col
              << guess.row << std::endl;
  }
};

class EasyAIPlayer : public AIPlayer {
 public:
  void init(WordLoader& wordloader) override;
  Guess guess(Grid& grid) override;

 private:
  int make_radom_guess();
};

#endif  // AIPLAYER_H