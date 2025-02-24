#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <bitset>
#include <iostream>
struct Keyboard {
  Keyboard() = default;
  void display(
      const std::bitset<26>& invalid_grid_letters,
      const std::bitset<26>& invalid_cell_letters = std::bitset<26>()) const {
    const std::bitset<26>& invalid_letters =
        invalid_grid_letters | invalid_cell_letters;

    auto getchar = [&invalid_letters](int index) -> char {
      return invalid_letters[index] ? ' ' : 'A' + index;
    };

    std::cout << "\n----------------------\n";
    std::cout << "| ";
    for (int i = 0; i < 9; i++) {
      std::cout << " " << getchar(i);
    }
    std::cout << " |\n|  ";
    for (int i = 9; i < 17; i++) {
      std::cout << " " << getchar(i);
    }
    std::cout << "  |\n| ";
    for (int i = 17; i < 26; i++) {
      std::cout << " " << getchar(i);
    }
    std::cout << " |\n";
  }
};

#endif  // KEYBOARD_H