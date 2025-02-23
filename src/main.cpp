#include <iostream>
#include <memory>

#include "Game.h"

int main() {
  Game game("wordlist.csv");
  game.run();

  return 0;
}