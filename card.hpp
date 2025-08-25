#ifndef EL_CARD_HPP
#define EL_CARD_HPP
#include <string>
#include <vector>

namespace el {

struct Card {
  std::string suit_;
  std::string range_;
  int game_value_;

  Card(const std::string &suit_, const std::string &range_,
       int const game_value_);
};

bool operator==(const Card &one, const Card &other);

class Deck {
  std::vector<Card> deck_;

 public:
  Deck();

  void shuffle();

  Card topCard();

  size_t size() const;

  const std::vector<Card> &get_deck() const;
};
}  
#endif