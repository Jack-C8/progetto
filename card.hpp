#ifndef EL_CARD_HPP
#define EL_CARD_HPP
#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace el {

class Card {
 public:
  std::string suit_;
  std::string range_;
  int game_value_;

  Card(const std::string& suit_, const std::string& range_,
       int const& game_value_);
};

bool operator==(const Card& one, const Card& other);

class Deck {
  std::vector<Card> deck_;

 public:
  Deck();

  void shuffle();

  Card topCard();

  unsigned int size() const;

  const std::vector<Card> &getDeck() const;
};
}  // namespace el
#endif