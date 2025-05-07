#ifndef EL_CARD_HPP
#define EL_CARD_HPP

namespace el {

struct Card {
  std::string suit_;
  std::string range_;
  int game_value_;
  bool face_;

  Card(const std::string &suit, const std::string &range, int const game_value);
};

bool operator==(const Card &one, const Card &other);

class Deck {
  std::vector<Card> deck_;

 public:
  Deck();

  void shuffle();

  Card topCard();

  size_t deck_size() const;

  const std::vector<Card> &get_deck() const;
};
}  // namespace el
#endif