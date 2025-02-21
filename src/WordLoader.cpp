#include "WordLoader.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

WordLoader::WordLoader(const std::string& filename) {
  file_.open(filename);
  if (!file_.is_open() || file_.fail()) {
    std::runtime_error("Failed to open file");
  }
  std::string word;
  while (std::getline(file_, word)) {
    words_.push_back(word);
  }

  file_.close();
  std::cout << "Loaded " << words_.size() << " words" << std::endl;
}

WordLoader::~WordLoader() {
  if (file_.is_open()) {
    file_.close();
  }
}

std::vector<std::string> WordLoader::sample_words(const int num_words) {
  if (num_words > kMaxWords_) {
    std::runtime_error("Too many words requested");
  }
  std::vector<std::string> words;
  words.reserve(num_words);
  std::srand(std::time(nullptr));
  int counter = 0;
  while (counter < num_words) {
    const int index = std::rand() % words_.size();
    if (std::find(used_indices_.begin(), used_indices_.end(), index) ==
        used_indices_.end()) {
      used_indices_.push_back(index);
      words.push_back(words_[index]);
      counter++;
    }
  }
  return words;
}
