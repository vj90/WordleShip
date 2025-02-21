#ifndef WORDLOADER_H
#define WORDLOADER_H
#include <fstream>
#include <string>
#include <vector>

class WordLoader {
 public:
  WordLoader(const std::string& filename);
  std::vector<std::string> get_words() const { return words_; }
  ~WordLoader();

  WordLoader(const WordLoader&) = delete;
  WordLoader& operator=(const WordLoader&) = delete;
  WordLoader(WordLoader&&) = delete;
  WordLoader& operator=(WordLoader&&) = delete;
  std::vector<std::string> sample_words(const int num_words = 5);

 private:
  std::vector<std::string> words_;
  std::ifstream file_;
  std::vector<int> used_indices_;  // to ensure unique words in the entire game
  static const int kMaxWords_ = 1000;  // TODO handle this better
};

#endif  // WORDLOADER_H