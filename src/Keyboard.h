#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <bitset>
#include <iostream>
struct Keyboard {
  static constexpr int kNumLetters{26};
  Keyboard() = default;
  void display(const std::bitset<kNumLetters>& invalid_grid_letters,
               const std::bitset<kNumLetters>& invalid_cell_letters =
                   std::bitset<kNumLetters>()) const {
    const std::bitset<26>& invalid_letters =
        invalid_grid_letters | invalid_cell_letters;

    auto getchar = [&invalid_letters](int index) -> char {
      return invalid_letters[index] ? ' ' : 'A' + index;
    };

    std::cout << "\n----------------------\n";
    std::cout << "| ";
    constexpr int num_letters_in_row = 9;
    for (int i = 0; i < num_letters_in_row; i++) {
      std::cout << " " << getchar(i);
    }
    std::cout << " |\n|  ";
    for (int i = num_letters_in_row; i < 2 * num_letters_in_row - 1; i++) {
      std::cout << " " << getchar(i);
    }
    std::cout << "  |\n| ";
    for (int i = 2 * num_letters_in_row - 1; i < kNumLetters; i++) {
      std::cout << " " << getchar(i);
    }
    std::cout << " |\n";
  }
};

#endif  // KEYBOARD_H