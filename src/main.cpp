#include <iostream>
#include <memory>

#include "Game.h"
#include "GameParams.h"
#include "Grid.h"
#include "WordLoader.h"

int main() {
  Game game("wordlist.csv");
  bool exit{false};
  bool game_over{false};
  int num_guesses{0};

  game.run();

  return 0;
}