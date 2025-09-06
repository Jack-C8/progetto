#ifndef EL_CARD_HPP
#define EL_CARD_HPP
#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace el {

class Card {
  std::string suit_;
  std::string range_;
  int game_value_;

 public:
  Card(const std::string &suit_, const std::string &range_,
       int const game_value_);
  std::string getSuit() const { return suit_; }
  std::string getRange() const { return range_; }
  int getGameValue() const { return game_value_; }
  bool operator==(const Card &other) const;
};

class Deck {
  std::vector<Card> deck_;

 public:
  Deck();
  void shuffle();
  Card topCard();
  size_t size() const;
  const std::vector<Card>& getDeck() const;
};
}  // namespace el
#endif